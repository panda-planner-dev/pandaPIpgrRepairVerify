#include <iostream>
#include "htnModel/Model.h"
#include "verification/GroundVerifier.h"
#include <vector>
#include <sys/time.h>


using namespace std;
using namespace progression;

int main(int argc, char *argv[]) {

    cout << "HTN Plan Verification as HTN Planning." << endl;
    cout << "verificationAsPlanning pandagrounding sasplan" << endl;

#ifndef NDEBUG
    cout
            << "You have compiled  without setting the NDEBUG flag. This will make it slow and should only be done for debug."
            << endl;
#endif
    string s;
    timeval tp;
    s = argv[1];
    gettimeofday(&tp, NULL);
    long startT = tp.tv_sec * 1000 + tp.tv_usec / 1000;

    cout << "Reading HTN model from file \"" << s << "\" ... " << endl;
    Model *htn = new Model();
    htn->filename = s;
    htn->read(s);
    long endT = tp.tv_sec * 1000 + tp.tv_usec / 1000;
    cout << "- [timePrepareModel=" << (endT - startT) << "]" << endl;
    startT = endT;

    cout << "Creating verify problem." << endl;
    GroundVerifier v;
    string sasPlan = argv[2];
    v.verify(htn, sasPlan);
    gettimeofday(&tp, NULL);
    endT = tp.tv_sec * 1000 + tp.tv_usec / 1000;
    cout << "- [timeCreatingVerifyproblem=" << (endT - startT) << "]" << endl;
    exit(0);
}
