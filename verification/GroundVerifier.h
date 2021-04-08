//
// Created by dh on 28.10.20.
//

#ifndef TOSTRIPSAPPROXIMATION_GROUNDVERIFIER_H
#define TOSTRIPSAPPROXIMATION_GROUNDVERIFIER_H


#include "../htnModel/Model.h"

class GroundVerifier {

public:
    void verify(progression::Model *htn, string sasPlan);

    void writeAction(Model *pModel, ofstream& ofstream, int iAction, int pFrom, int last1);
};


#endif //TOSTRIPSAPPROXIMATION_GROUNDVERIFIER_H
