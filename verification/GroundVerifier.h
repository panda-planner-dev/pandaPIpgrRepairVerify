//
// Created by Daniel Höller on 28.10.20.
//

#ifndef GROUNDVERIFIER_H
#define GROUNDVERIFIER_H


#include "../htnModel/Model.h"

class GroundVerifier {

public:
    void verify(progression::Model *htn, string sasPlan);

    void writeAction(Model *pModel, ofstream& ofstream, int iAction, int pFrom, int last1);

    bool isAppliable(const Model *htn, unordered_set<int> &state, int a) const;
};


#endif //GROUNDVERIFIER_H
