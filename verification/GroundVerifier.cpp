//
// Created by Daniel Höller on 28.10.20.
//

#include <fstream>
#include <map>
#include <unordered_map>
#include "GroundVerifier.h"
#include <cassert>
#include <algorithm>
#include <list>

void GroundVerifier::verify(progression::Model *htn, string sasPlan) {
    //
    // read plan
    //

    std::ifstream fIn(sasPlan);

    vector<string> plan;
    std::string line;

    // read plan from file
    while (std::getline(fIn, line)) {
        int i = line.find(")(");
        while (i != std::string::npos) { // split lines with multiple actions in it
            string action = line.substr(0, i + 1);
            line = line.substr(i + 1, line.length());
            plan.push_back(action);
            i = line.find(")(");
        }
        plan.push_back(line);
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

        if (htn->taskNames[i].rfind("__") == 0) { // technical actions start with two underscores
            technicalActions.insert(i);
        }
    }

    // generate set of distinct actions and sequence of plan steps
    vector<int> prefix;
    set<int> distinctActions;
    bool usinglowercase = false;
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
            for (int i = 0; i < htn->numActions; i++) {
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
                distinctActions.insert(i);
                usinglowercase = true;
                continue;
            }
            cout << "ERROR: task name not found: " << line << endl;
            exit(-1);
        } else {
            int i = iter->second;
            prefix.push_back(i);
            distinctActions.insert(i);
        }
    }
    delete taskNameMapping;
    fIn.close();

    list<int> techWithAdd;
    for (int a : technicalActions) {
        if (htn->numAdds[a] > 0) {
            techWithAdd.push_back(a);
        }
    }
    cout << "- detecting reachable technical actions" << endl;
    if (techWithAdd.empty()) {
        cout << "- using exact states." << endl;
        unordered_set<int> state;
        for (int i = 0; i < htn->s0Size; i++) {
            state.insert(htn->s0List[i]);
        }
        list<int> unapplicable;
        for (int a : technicalActions) {
            if (!isAppliable(htn, state, a)) {
                unapplicable.push_back(a);
            }
        }
        for (int a : prefix) {
            for (int j = 0; j < htn->numDels[a]; j++) {
                state.erase(htn->delLists[a][j]);
            }
            for (int j = 0; j < htn->numAdds[a]; j++) {
                state.insert(htn->addLists[a][j]);
            }
            for (int j = 0; j < unapplicable.size(); j++) {
                int a2 = unapplicable.front();
                unapplicable.pop_front();
                if (!isAppliable(htn, state, a2)) {
                   unapplicable.push_back(a2);
                }
            }
        }
        cout << "- pruning " << unapplicable.size() << " from " << technicalActions.size() << " technical actions." << endl;
        for (int a : unapplicable) {
            technicalActions.erase(a);
        }
    } else {
        cout << "- using delete-relaxed states." << endl;
        unordered_set<int> state;
        for (int i = 0; i < htn->s0Size; i++) {
            state.insert(htn->s0List[i]);
        }
        for (int a : distinctActions) {
            for (int j = 0; j < htn->numAdds[a]; j++) {
                state.insert(htn->addLists[a][j]);
            }
        }
        bool changed = true;
        while (changed) {
            changed = false;
            for (int i = 0; i  < techWithAdd.size(); i++) {
                int a = techWithAdd.front();
                techWithAdd.pop_front();
                if (isAppliable(htn, state, a)) {
                    changed = true;
                    for (int j = 0; j < htn->numAdds[a]; j++) {
                        state.insert(htn->addLists[a][j]);
                    }
                } else {
                    techWithAdd.push_back(a);
                }
            }
        }
        for (int a : techWithAdd) {
            technicalActions.erase(a);
        }
        for (auto iter = technicalActions.begin(); iter != technicalActions.end();) {
            int a = *iter;
            if (!isAppliable(htn, state, a)) {
               iter = technicalActions.erase(iter);
            } else {
                iter++;
            }
        }
    }
    /*
     * bottom-up reachability
     */
    cout << "- detecting unreachable tasks bottom-up" << endl;

    int* methodST = new int[htn->numMethods];
    for (int i = 0; i < htn->numMethods; i++) {
        methodST[i] = htn->numDistinctSTs[i];
    }
    unordered_set<int> buReachableT;
    unordered_set<int> buReachableM;
    vector<int> fringe;

    fringe.reserve(distinctActions.size());
    for (int action : distinctActions) {
        fringe.push_back(action);
    }
    for (int action : technicalActions) {
        fringe.push_back(action);
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
    if (buReachableT.find(htn->initialTask) == buReachableT.end()) {
        cout << "Verification problem proven UNSOLVABLE via reachability analysis." << endl;
        exit(0);
    }
    delete[] methodST;

    /*
     * top-down reachability
     */
    cout << "- detecting top-down reachable tasks" << endl;
    set<int> *tdReachableT = new set<int>;
    set<int> *tdReachableM = new set<int>;
    fringe.clear();
    fringe.push_back(htn->initialTask);
    tdReachableT->insert(htn->initialTask);
    while (!fringe.empty()) {
        int t = fringe.back();
        fringe.pop_back();
        if (buReachableT.find(t) == buReachableT.end())
            continue;
        for (int i = 0; i < htn->numMethodsForTask[t]; i++) {
            int m = htn->taskToMethods[t][i];
            if (buReachableM.find(m) == buReachableM.end())
                continue;
            tdReachableM->insert(m);
            for (int j = 0; j < htn->numSubTasks[m]; j++) {
                int subt = htn->subTasks[m][j];
                if (tdReachableT->find(subt) == tdReachableT->end()) {
                    tdReachableT->insert(subt);
                    fringe.push_back(subt);
                }
            }
        }
    }
    for (int action : distinctActions) {
        if (tdReachableT->find(action) == tdReachableT->end()) {
            cout << "Verification problem proven UNSOLVABLE via reachability analysis." << endl;
            exit(0);
        }
    }

    cout << "- writing verify problem" << endl;
    // prepare things
    int numNewBits = prefix.size() + 2;
    for(auto iter = technicalActions.begin(); iter != technicalActions.end();) {
        int a = *iter;
        if (tdReachableT->find(a) == tdReachableT->end()) {
            iter = technicalActions.erase(iter);
        } else {
            ++iter;
        }
    }

    for (int t : *tdReachableT) {
        string actionName = htn->taskNames[t];
	 	if (htn->taskNames[t].rfind("__") == 0 && t < htn->numActions) { // these actions start with two underscores
            technicalActions.insert(t);
        }
    }

    // new task structure:
    // ppptttccccnnn
    // - p: copies of actions, one for each action in prefix (as many as there are actions in prefix)
    // - t: technical actions that are kept (e.g. method precs)
    // - c: abstract tasks contained in original model
    // - n: newly introduced abstract tasks (as many as there are distinct tasks in prefix)

    map<int, int> old2new;
    int current = prefix.size();
    for (int i : technicalActions) {
        old2new[i] = current++;
    }
    for (int i = htn->numActions; i < htn->numTasks; i++) {
        if (tdReachableT->find(i) != tdReachableT->end()) {
            old2new[i] = current++;
        }
    }

    // mapping from actions contained in the prefix to the new abstract tasks
    map<int, int> prim2abs;
    for (int a : distinctActions) {
        prim2abs[a] = current++;
        old2new[a] = prim2abs[a];
    }

    //
    // encode problem
    //
    string outFileName = sasPlan.append(".verify");
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
    int first = htn->lastIndex[htn->numVars - 1] + 1;
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
    fOut << (prefix.size() + technicalActions.size()) << endl;
    for (int i = 0; i < prefix.size(); i++) {
        writeAction(htn, fOut, prefix[i], first + i, first + i + 1);
    }
    for (int t : technicalActions) {
        writeAction(htn, fOut, t, -1, -1);
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
    int numTasks = tdReachableT->size() + prefix.size();
    fOut << numTasks << endl;
    int check = 0;
    for (int i = 0; i < prefix.size(); i++) {
        fOut << "0 " << htn->taskNames[prefix[i]] << endl;
        check++;
    }
    for (int t : technicalActions) {
        fOut << "0 " << htn->taskNames[t] << endl;
		check++;
    }
    for (int i = htn->numActions; i < htn->numTasks; i++) {
        if (tdReachableT->find(i) != tdReachableT->end()) {
            fOut << "1 " << htn->taskNames[i] << endl;
            check++;
        }
    }
    for (int t : distinctActions) {
        fOut << "1 <abs>" << htn->taskNames[t] << endl;
        check++;
    }
    if (check != numTasks) {
        cout << "ERROR: creation of verify problem failed" << endl;
        exit(-1);
    }

    fOut << endl << ";; initial abstract task" << endl;
    fOut << old2new[htn->initialTask] << endl;

    fOut << endl << ";; methods" << endl;
    int numMethods = tdReachableM->size() + prefix.size();
    fOut << numMethods << endl;
    check = 0;
    for (int i = 0; i < htn->numMethods; i++) {
        if (tdReachableM->find(i) != tdReachableM->end()) {
            fOut << htn->methodNames[i] << endl;
            fOut << old2new[htn->decomposedTask[i]] << endl;
            for (int j = 0; j < htn->numSubTasks[i]; j++) {
                fOut << old2new[htn->subTasks[i][j]] << " ";
            }
            fOut << "-1" << endl;
            for (int j = 0; j < htn->numOrderings[i]; j++) {
                fOut << htn->ordering[i][j] << " ";
            }
            fOut << "-1" << endl;
            check++;
        }
    }

    // methods from new abstract tasks to prefix copies
    for (int i = 0; i < prefix.size(); i++) {
        int a = prefix[i];
        fOut << "__<method2pref" << i << ">" << htn->taskNames[a] << endl;
        fOut << prim2abs[a] << endl;
        fOut << i << " -1" << endl;
        fOut << "-1" << endl; // ordering relations
        check++;
    }
    assert(check == numMethods);

    fOut.close();
}

bool GroundVerifier::isAppliable(const Model *htn, unordered_set<int> &state, int a) const {
    for (int j = 0; j < htn->numPrecs[a]; j++) {
        if (state.find(htn->precLists[a][j]) == state.end()) {
            return false;
        }
    }
    return true;
}

void GroundVerifier::writeAction(Model *htn, ofstream &fOut, int iAction, int pFrom, int pTo) {
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
    if (pFrom >= 0) {
        fOut << "0 " << pFrom << " "; // add del effect
    }
    fOut << "-1" << endl;
}
