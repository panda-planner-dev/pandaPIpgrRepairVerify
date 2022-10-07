//
// Created by Daniel Höller on 28.10.20.
//

#ifndef GROUNDVERIFIER_H
#define GROUNDVERIFIER_H


#include "../htnModel/Model.h"

enum encodingType {Verification, PGRfo, PGRpo, Repair};

class GroundPrefixEncoding {

public:
    void prefixEncoding(Model *htn, string sasPlan, encodingType enc, bool techVisible, int i);

    void writeAction(ofstream &fOut, int iAction, int pFrom, int pTo);

    bool isApplicable(const Model *htn, unordered_set<int> &state, int a) const;

    bool readSolution(const string &filename, vector<string> &plan_out, int stopAfter);

    encodingType encode = Verification;

    Model *htn;


    void doVerifyPruning(set<int> &technicalActions, vector<int> &prefix, set<int> &distinctActions) const;

    bool bottomUpReachability(set<int> &technicalActions, set<int> &distinctActions, unordered_set<int> &buReachableT, unordered_set<int> &buReachableM);

    void topDownReachability(unordered_set<int> &buReachableT, unordered_set<int> &buReachableM, set<int> &tdReachableT, set<int> &tdReachableM);

    void cleanStr(string &action) const;
};


#endif //GROUNDVERIFIER_H
