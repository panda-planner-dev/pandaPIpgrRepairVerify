#include <iostream>
#include "htnModel/Model.h"
#include "prefEncoding/GroundPrefixEncoding.h"
#include <vector>
#include <sys/time.h>


using namespace std;
using namespace progression;

int main(int argc, char *argv[]) {
    bool printAndExit = false;
    bool techVisible = false;
    int stopAfter = -1;
    encodingType encodingTask;
    if (argc < 4) {
        printAndExit = true;
    } else {
        string task = argv[1];
        if (task.compare("pgrfo") == 0) {
            encodingTask = PGRfo;
            if (argc == 5) {
                string stopCondition = argv[4];
                stopAfter = stoi(stopCondition);
            }
        } else if (task.compare("pgrpo") == 0) {
            encodingTask = PGRpo;
            if (argc == 5) {
                string stopCondition = argv[4];
                stopAfter = stoi(stopCondition);
            }
        } else if (task.compare("repair") == 0) {
            encodingTask = Repair;
            cout << "repair is not yet implemented..." << endl;
            exit(-1);
        } else if (task.compare("verify") == 0) {
            encodingTask = Verification;
        } else if (task.compare("verify-all") == 0) {
            encodingTask = Verification;
            techVisible = true;
        } else {
            printAndExit = true;
        }
    }
    if (printAndExit) {
        cout << "HTN prefix encoding, which can be used for:" << endl;
        cout << "- plan and goal recognition as planning, fully observable setting [pgrfo]" << endl;
        cout << "- plan and goal recognition as planning, partially observable setting [pgrpo]" << endl;
        cout << "- plan repair as planning [repair]" << endl;
        cout << "- plan verification as planning [verify]" << endl;
        cout << "- plan verification as planning [verify-all], but with technical actions included in the sequence (e.g. used by TOAD)" << endl;
        cout << "<executable> [pgrfo|pgrpo|repair|verify|verify-all] pandagrounding plan[-prefix]" << endl;
        exit(-1);
    }
#ifndef NDEBUG
    cout << "You have compiled  without setting the NDEBUG flag. This will make it slow and should only be done for debug." << endl;
#endif
    string s;
    timeval tp;
    s = argv[2];
    gettimeofday(&tp, NULL);
    long startT = tp.tv_sec * 1000 + tp.tv_usec / 1000;

    cout << "Reading HTN model from file \"" << s << "\" ... " << endl;
    Model *htn = new Model();
    htn->filename = s;
    htn->read(s);
    long endT = tp.tv_sec * 1000 + tp.tv_usec / 1000;
    cout << "- [timePrepareModel=" << (endT - startT) << "]" << endl;
    startT = endT;

    cout << "Creating problem." << endl;
    GroundPrefixEncoding v;
    string solution = argv[3];
    v.prefixEncoding(htn, solution, encodingTask, techVisible, stopAfter);
    gettimeofday(&tp, NULL);
    endT = tp.tv_sec * 1000 + tp.tv_usec / 1000;
    cout << "- [timeCreatingVerifyproblem=" << (endT - startT) << "]" << endl;
    exit(0);
}
