//
// Created by Daniel Höller on 28.10.20.
//

#include <fstream>
#include <map>
#include <unordered_map>
#include "GroundPrefixEncoding.h"
#include <cassert>
#include <algorithm>
#include <list>


void GroundPrefixEncoding::prefixEncoding(Model *htn, string sasPlan, encodingType enc, bool techVisible, int stopAfter) {
    //
    // read plan
    //
    this->htn = htn;
    this->encode = enc;

    vector<string> plan;
    bool fullsol = readSolution(sasPlan, plan, stopAfter); // returns whether the entire solution is parsed
    string filePostPix;
    if (fullsol) {
        filePostPix = "-full";
    } else {
        if (stopAfter < 10) {
            filePostPix = "-00" + to_string(stopAfter);
        } else if (stopAfter < 100) {
            filePostPix = "-0" + to_string(stopAfter);
        } else {
            filePostPix = "-" + to_string(stopAfter);
        }
    }

    unordered_map<string, int>* taskNameMapping = new unordered_map<string, int>;
    set<int> technicalActions;
    for (int i = 0; i < htn->numActions; i++) {
#ifndef NDEBUG
        if (taskNameMapping->find(htn->taskNames[i]) != taskNameMapping->end()) {
            cout << "ERROR: Found two actions with same name" << endl;
            exit(-1);
        }
#endif
        taskNameMapping->insert({htn->taskNames[i], i});

        if ((!techVisible) && (htn->taskNames[i].rfind("__") == 0)) { // technical actions start with two underscores
            technicalActions.insert(i);
        }
    }

    // generate set of distinct actions and sequence of plan steps
    vector<int> prefix;
    set<int> distPrefActions; // distinct actions in prefix
    bool usinglowercase = false;
    string line;
    for (int i = 0; i < plan.size(); i++) {
        line = plan[i];
        if (usinglowercase) {
            transform(line.begin(), line.end(), line.begin(), [](unsigned char c){ if (c == '-') return int('_'); return tolower(c); });
        }
        if (line.rfind(';') == 0) continue; // skip comments
        line = line.substr(1, line.length() - 2);
        if (line.rfind("epsilon") == 0) continue; // skip epsilon actions from TOAD

        auto iter = taskNameMapping->find(line);
        if (iter == taskNameMapping->end()) {
            // try with lower case
            cout << "- Did not find action \"" << line << "\", trying lower case." << endl;
            taskNameMapping->clear();
            for (int i = 0; i < htn->numActions; i++) { // todo: kill this
                string name = htn->taskNames[i];
                transform(name.begin(), name.end(), name.begin(), [](unsigned char c){ if (c == '-') return int('_'); return tolower(c); });
                if (taskNameMapping->find(htn->taskNames[i]) != taskNameMapping->end()) {
                    cout << "ERROR: Found two actions with same name" << endl;
                    exit(-1);
                }
                taskNameMapping->insert({name, i});
            }
            transform(line.begin(), line.end(), line.begin(), [](unsigned char c){ if (c == '-') return int('_'); return tolower(c); });
            iter = taskNameMapping->find(line);
            if (iter != taskNameMapping->end()) {
                cout << "WARNING: Did not find mixed-case name of action, using lower case." << endl;
                int i = iter->second;
                prefix.push_back(i);
                distPrefActions.insert(i);
                usinglowercase = true;
                continue;
            }
            cout << "ERROR: task name not found: " << line << endl;
            exit(-1);
        } else {
            int i = iter->second;
            prefix.push_back(i);
            distPrefActions.insert(i);
        }
    }
    delete taskNameMapping;

    if (encode == Verification) {
        // for verification, we know very much about the state space and can do a special state-based pruning
        doVerifyPruning(technicalActions, prefix, distPrefActions);
    }

    /*
     * reachability analysis
     */

    unordered_set<int> buReachableT;
    unordered_set<int> buReachableM;
    set<int> tdReachableT;
    set<int> tdReachableM;

    bool writeDummy = bottomUpReachability(technicalActions, distPrefActions, buReachableT, buReachableM);
    if (buReachableT.find(htn->initialTask) == buReachableT.end()) {
        cout << "Verification problem proven UNSOLVABLE via reachability analysis." << endl;
        exit(0);
    }

    topDownReachability(buReachableT, buReachableM, tdReachableT, tdReachableM);
    for (int action : distPrefActions) { // check whether prefix got unreachable
        if (tdReachableT.find(action) == tdReachableT.end()) {
            cout << "Verification problem proven UNSOLVABLE via reachability analysis." << endl;
            exit(0);
        }
    }

    cout << "- writing transformed problem" << endl;
    int numNewBits = prefix.size() + 2;

    // new task structure:
    // ppptttccccnnn
    // - p: copies of actions, one for each action in prefix (as many as there are actions in prefix)
    // - t: actions that are kept
    //   - for verification, these are the technical actions
    //   - for repair and pgr, these are also other actions (with the pruning currently implemented, these are all actions)
    // - c: abstract tasks contained in original model
    // - n: newly introduced abstract tasks (as many as there are distinct tasks in prefix)

    // determine which tasks need to be written
    // - the prefix (type "p" from above) is already created and its reachability is checked
    set<int> typeTactions; // type "t" from above
    set<int> absTasks; // type "c"
    for (int t : tdReachableT) {
        if (t < htn->numActions) {
            if ((encode != Verification) || (distPrefActions.find(t) == distPrefActions.end())) {
                // for prefixEncoding, there do not need to be copies of the prefix actions, for repair and pgr, there must be
                typeTactions.insert(t);
            }
        } else  {
            absTasks.insert(t);
        }
    }

    map<int, int> old2new;
    map<int, int> distinctToTypeT;
    int current = prefix.size();
    for (int i: typeTactions) {
        if (distPrefActions.find(i) == distPrefActions.end()) {
            old2new[i] = current++;
        } else {
            // this action is also contained in the prefix
            // - it will be replaced in all method by that abstract task
            // - here I need two mappings:
            //   - in the subtask, i will be replaced by the new abstract task (stored in old2new and set below)
            //   - (for r and pgr) I need to introduce a method to the original action, this is stored here:
            distinctToTypeT[i] = current++;
        }
    }
    int dummyTaskID = -1;
    if (writeDummy) {
        dummyTaskID =  current++; // the dummy task is inserted after the original actions
    }
    for (int i: absTasks) {
        old2new[i] = current++;
    }

    // mapping from actions contained in the prefix to the new abstract tasks
    map<int, int> prim2abs;
    for (int a : distPrefActions) {
        prim2abs[a] = current++;
        old2new[a] = prim2abs[a];
    }

    //
    // encode problem
    //
    string outFileName;
    if (encode == Verification) {
        outFileName = sasPlan.append(".prefixEncoding");
    }  else if ((encode == PGRfo) || (encode == PGRpo)) {
        outFileName = sasPlan.append(filePostPix + ".pgr");
    }  else {
        outFileName = sasPlan.append(".repair");
    }

    std::ofstream fOut(outFileName);
    fOut << ";; #state features" << endl;
    fOut << (htn->numStateBits + numNewBits) << endl;
    for (int i = 0; i < htn->numStateBits; i++) {
        fOut << htn->factStrs[i] << endl;
    }
    for (int i = 0; i < numNewBits; i++) {
        fOut << "prefpos" << i << endl;
    }

    fOut << endl << ";; Mutex Groups" << endl;
    fOut << (htn->numVars + 1) << endl;
    for (int i = 0; i < htn->numVars; i++) {
        fOut << htn->firstIndex[i] << " " << htn->lastIndex[i] << " " << htn->varNames[i] << endl;
    }
    int first;
    if (htn->numVars == 0) {
        first = 0;
    } else {
        first = htn->lastIndex[htn->numVars - 1] + 1;
    }
    int last = first + numNewBits - 1;
    fOut << first << " " << last << " prefixOrdering" << endl;

    fOut << endl << ";; further strict Mutex Groups" << endl;
    fOut << htn->numStrictMutexes << endl;
    for (int i = 0; i < htn->numStrictMutexes; i++) {
        fOut << htn->strictMutexes[i][0] << " " << htn->strictMutexes[i][1] << " -1" << endl;
    }

    fOut << endl << ";; further non strict Mutex Groups" << endl;
    fOut << htn->numMutexes << endl;
    for (int i = 0; i < htn->numMutexes; i++) {
        fOut << htn->mutexes[i][0] << " " << htn->mutexes[i][1] << " -1" << endl;
    }

    fOut << endl << ";; known invariants" << endl;
    fOut << htn->numInvariants << endl;
    for (int i = 0; i < htn->numInvariants; i++) {
        fOut << htn->invariants[i][0] << " " << htn->invariants[i][1] << " -1" << endl;
    }

    fOut << endl << ";; Actions" << endl;
    int numActions = prefix.size() + typeTactions.size();
    if (writeDummy) {
        numActions++;
    }
    fOut << (numActions) << endl;
    for (int i = 0; i < prefix.size(); i++) {
        // todo for repair: add the additional effects to the last action
        writeAction(fOut, prefix[i], first + i, first + i + 1);
    }
    for (int t : typeTactions) {
        int prec = -1;
        if ((encode == PGRfo) || ( encode == Repair)) {
            if (technicalActions.find(t) == technicalActions.end()) {
                prec = last - 1; // non-technical actions need to be placed after prefix
            }
        }
        writeAction(fOut, t, prec, -1);
    }
    if (writeDummy) {
        fOut << "1\n-1\n-1\n-1\n";
    }
    fOut << endl << ";; initial state" << endl;
    for (int i = 0; i < htn->s0Size; i++) {
        fOut << htn->s0List[i] << " ";
    }
    fOut << first << " -1" << endl;

    fOut << endl << ";; goal" << endl;
    for (int i = 0; i < htn->gSize; i++) {
        fOut << htn->gList[i] << " ";
    }
    fOut << last - 1 << " -1" << endl;

    fOut << endl << ";; tasks (primitive and abstract)" << endl;
    //int numTasks = tdReachableT.size() + prefix.size();
    int numTasks = tdReachableT.size() + distPrefActions.size() + prefix.size();
    // - reachable contains all tasks, i.e., the original actions
    // - for each distinct task in the prefix, there will be an additional abstract task
    // - for each task in the prefix, there will be an additional primitive action
    if (writeDummy) {
        numTasks++;
    }
    fOut << numTasks << endl;

    int check = 0;
    for (int i = 0; i < prefix.size(); i++) {
        fOut << "0 " << htn->taskNames[prefix[i]] << endl;
        check++;
    }
    for (int t : typeTactions) {
        fOut << "0 " << htn->taskNames[t] << endl;
		check++;
    }
    if (writeDummy) {
        fOut << "0 EPSILONTASK[]" << endl;
        check++;
    }
    for (int i : absTasks) {
        fOut << "1 " << htn->taskNames[i] << endl;
        check++;
    }
    for (int t : distPrefActions) {
        fOut << "1 <abs>" << htn->taskNames[t] << endl;
        check++;
    }
    if (check != numTasks) {
        cout << "ERROR: check sums note correct." << endl;
        cout << "       number of actions " << check << " expected " << numTasks << endl;
        cout << "       creation of transformed problem failed." << endl;
        exit(-1);
    }

    fOut << endl << ";; initial abstract task" << endl;
    fOut << old2new[htn->initialTask] << endl;

    fOut << endl << ";; methods" << endl;
    int numMethods = tdReachableM.size() + prefix.size();
    // - for each task in the prefix, there will be an additional method
    if((encode == PGRfo) || (encode == PGRpo) || (encode == Repair)) {
        // - for pgr and repair, the actions are also allowed after the prefix, this adds another method per *distinct* action in prefix
        numMethods += distPrefActions.size();
    }
    fOut << numMethods << endl;

    check = 0;
    for (int i : tdReachableM) {
        fOut << htn->methodNames[i] << endl;
        fOut << old2new[htn->decomposedTask[i]] << endl;
        if (htn->numSubTasks[i] == 0) {
            fOut << dummyTaskID << " ";
        } else {
            for (int j = 0; j < htn->numSubTasks[i]; j++) {
                fOut << old2new[htn->subTasks[i][j]] << " ";
            }
        }
        fOut << "-1" << endl;
        for (int j = 0; j < htn->numOrderings[i]; j++) {
            fOut << htn->ordering[i][j] << " ";
        }
        fOut << "-1" << endl;
        check++;
    }

    // methods from new abstract tasks to prefix copies
    for (int i = 0; i < prefix.size(); i++) {
        int a = prefix[i];
        fOut << "_!<method2pref" << i << ">" << htn->taskNames[a] << endl;
        fOut << prim2abs[a] << endl;
        fOut << i << " -1" << endl;
        fOut << "-1" << endl; // ordering relations
        check++;
    }

    // methods from new abstract tasks to original actions
    if ((encode == PGRfo) || (encode == PGRpo) || (encode == Repair)) {
        for (int a: distPrefActions) {
            fOut << "_!<method2org>" << htn->taskNames[a] << endl;
            fOut << prim2abs[a] << endl; // this is the mapping from the action to the new abstract task
            fOut << distinctToTypeT[a] << " -1"
                 << endl; // this is the mapping to the original (non-prefix) copy of the action
            fOut << "-1" << endl; // ordering relations
            check++;
        }
    }
    assert(check == numMethods);

    fOut.close();
}

void GroundPrefixEncoding::topDownReachability(unordered_set<int> &buReachableT, unordered_set<int> &buReachableM,
                                               set<int> &tdReachableT, set<int> &tdReachableM) {
    cout << "- detecting top-down reachable tasks" << endl;
    vector<int> fringe;
    fringe.push_back(htn->initialTask);
    tdReachableT.insert(htn->initialTask);
    while (!fringe.empty()) {
        int t = fringe.back();
        fringe.pop_back();
        if (buReachableT.find(t) == buReachableT.end())
            continue;
        for (int i = 0; i < htn->numMethodsForTask[t]; i++) {
            int m = htn->taskToMethods[t][i];
            if (buReachableM.find(m) == buReachableM.end())
                continue;
            tdReachableM.insert(m);
            for (int j = 0; j < htn->numSubTasks[m]; j++) {
                int subt = htn->subTasks[m][j];
                if (tdReachableT.find(subt) == tdReachableT.end()) {
                    tdReachableT.insert(subt);
                    fringe.push_back(subt);
                }
            }
        }
    }
}

bool GroundPrefixEncoding::bottomUpReachability(set<int> &technicalActions, set<int> &distinctActions, unordered_set<int> &buReachableT, unordered_set<int> &buReachableM) {
    cout << "- detecting unreachable tasks bottom-up" << endl;
    int* methodST = new int[htn->numMethods];
    for (int i = 0; i < htn->numMethods; i++) {
        methodST[i] = htn->numDistinctSTs[i];
    }

    vector<int> fringe;
    if (encode == Verification) {
        // for repair, only actions from the solution sequence are reachable
        fringe.reserve(distinctActions.size());
        for (int action: distinctActions) {
            fringe.push_back(action);
        }
        for (int action: technicalActions) {
            fringe.push_back(action);
        }
    } else {
        // for both repair and PGR, all actions from the grounding are reachable
        // todo: this could be sharpened for some other cases (repair, sully obs. PGR, here you at least know the new start state)
        fringe.reserve(htn->numActions);
        for (int action = 0; action < htn->numActions; action++) {
            fringe.push_back(action);
        }
    }

    // handle empty methods
    bool writeDummy= false;
    for (int m = 0; m < htn->numMethods; m++) {
        if (htn->numSubTasks[m] == 0) {
            int t = htn->decomposedTask[m];
            if (buReachableT.find(t) == buReachableT.end()) { // must be also done here, there could be more than one method deleting t ;-)
                buReachableT.insert(t);
                fringe.push_back(t);
                buReachableM.insert(m);
                writeDummy = true; // need to add a dummy task to empty methods
            }
        }
    }

    while (!fringe.empty()) {
        int t = fringe.back();
        fringe.pop_back();
        for (int i = 0 ; i < htn->stToMethodNum[t]; i++) {
            int m = htn->stToMethod[t][i];
            if (--methodST[m] == 0) {
                buReachableM.insert(m);
                int t = htn->decomposedTask[m];
                if (buReachableT.find(t) == buReachableT.end()) {
                    buReachableT.insert(t);
                    fringe.push_back(t);
                }
            }
        }
    }
    delete[] methodST;
    return writeDummy;
}

void GroundPrefixEncoding::doVerifyPruning(set<int> &technicalActions, vector<int> &prefix, set<int> &distinctActions) const {
    list<int> techWithAdd;
    for (int a: technicalActions) {
        if (htn->numAdds[a] > 0) {
            techWithAdd.push_back(a);
        }
    }

    cout << "- detecting unreachable technical actions" << endl;
    if (techWithAdd.empty()) {
        cout << "- using exact states." << endl;
        unordered_set<int> state;
        for (int i = 0; i < htn->s0Size; i++) {
            state.insert(htn->s0List[i]);
        }
        list<int> unapplicable;
        for (int a: technicalActions) {
            if (!isApplicable(htn, state, a)) {
                unapplicable.push_back(a);
            }
        }
        for (int a: prefix) {
            for (int j = 0; j < htn->numDels[a]; j++) {
                state.erase(htn->delLists[a][j]);
            }
            for (int j = 0; j < htn->numAdds[a]; j++) {
                state.insert(htn->addLists[a][j]);
            }
            int size = unapplicable.size();
            for (int j = 0; j < size; j++) {
                int a2 = unapplicable.front();
                unapplicable.pop_front();
                if (!isApplicable(htn, state, a2)) {
                    unapplicable.push_back(a2);
                }
            }
        }
        cout << "- pruning " << unapplicable.size() << " from " << technicalActions.size() << " technical actions."
             << endl;
        for (int a: unapplicable) {
            technicalActions.erase(a);
        }
    } else {
        cout << "- using delete-relaxed states." << endl;
        unordered_set<int> state;
        for (int i = 0; i < htn->s0Size; i++) {
            state.insert(htn->s0List[i]);
        }
        for (int a: distinctActions) {
            for (int j = 0; j < htn->numAdds[a]; j++) {
                state.insert(htn->addLists[a][j]);
            }
        }
        bool changed = true;
        while (changed) {
            changed = false;
            int size = techWithAdd.size();
            for (int i = 0; i < size; i++) {
                int a = techWithAdd.front();
                techWithAdd.pop_front();
                if (isApplicable(htn, state, a)) {
                    changed = true;
                    for (int j = 0; j < htn->numAdds[a]; j++) {
                        state.insert(htn->addLists[a][j]);
                    }
                } else {
                    techWithAdd.push_back(a);
                }
            }
        }
        for (int a: techWithAdd) {
            technicalActions.erase(a);
        }
        for (auto iter = technicalActions.begin(); iter != technicalActions.end();) {
            int a = *iter;
            if (!isApplicable(htn, state, a)) {
                iter = technicalActions.erase(iter);
            } else {
                iter++;
            }
        }
    }
}

bool GroundPrefixEncoding::readSolution(const string &filename, vector<string> &plan_out, int stopafter) {
    ifstream fIn(filename);
    string line;
    int linesadded = 0;
    bool breakLoop = false;
    if (stopafter > 0) {
        while (getline(fIn, line)) {
            int i = line.find(")(");
            while (i != std::string::npos) { // split lines with multiple actions in it
                string action = line.substr(0, i + 1);
                line = line.substr(i + 1, line.length());

                if (action.find("]") == std::string::npos) {
                    cleanStr(action);
                }
                plan_out.push_back(action);
                if (plan_out.size() >= stopafter) {
                    breakLoop = true;
                    break;
                }
                i = line.find(")(");
            }
            if (breakLoop) {
                break;
            }
            cleanStr(line);
            plan_out.push_back(line);
            if ((stopafter >= 0) && (++linesadded == stopafter)) {
                break;
            }
        }
    }
    bool fileEnd = fIn.eof();
    if (fileEnd) {
        cout << "Parsed FULL solution (i.e., up to action " << plan_out.size() << ")" << endl;
    } else {
        cout << "Parsed solution up to action " << plan_out.size() << endl;
    }
    fIn.close();
    return fileEnd;
}

void GroundPrefixEncoding::cleanStr(string &action) const {
    int pos = action.find(" ");
    action.replace(pos, 1, "[");
    pos = action.length() - 1;
    action.insert(pos, 1, ']');
    pos = action.find(" ");
    while (pos != std::string::npos) {
        action.replace(pos, 1, ",");
        pos = action.find(" ");
    }
}

bool GroundPrefixEncoding::isApplicable(const Model *htn, unordered_set<int> &state, int a) const {
    for (int j = 0; j < htn->numPrecs[a]; j++) {
        if (state.find(htn->precLists[a][j]) == state.end()) {
            return false;
        }
    }
    return true;
}

void GroundPrefixEncoding::writeAction(ofstream &fOut, int iAction, int pFrom, int pTo) {
    fOut << htn->actionCosts[iAction] << endl;
    for (int j = 0; j < htn->numPrecs[iAction]; j++) {
        fOut << htn->precLists[iAction][j] << " ";
    }
    if (pFrom >= 0) {
        fOut << pFrom << " "; // add precondition
    }
    fOut << "-1" << endl;

    for (int j = 0; j < htn->numAdds[iAction]; j++) {
        fOut << "0 " << htn->addLists[iAction][j] << "  ";
    }
	if (pTo >= 0){
    	fOut << "0 " << pTo << " "; // add add effect
	}
    fOut << "-1" << endl;
    if ((htn->numConditionalAdds[iAction] > 0) || (htn->numConditionalDels[iAction] > 0)) {
        cout << "Conditional effects not supported" << endl;
        exit(-1);
    }

    for (int j = 0; j < htn->numDels[iAction]; j++) {
        fOut << "0 " << htn->delLists[iAction][j] << "  ";
    }
    if ((pFrom >= 0) && (pTo >= 0)) {
        fOut << "0 " << pFrom << " "; // add del effect
    }
    fOut << "-1" << endl;
}
