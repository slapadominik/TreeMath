//
// Created by Domicik on 07.12.2017.
//

#ifndef TREEMATH_RANDOMNODEGENERATOR_H
#define TREEMATH_RANDOMNODEGENERATOR_H


#include "CNode.h"

class RandomNodeGenerator {
public:
    static CNode& generateRandomNode();
    static std::string generateRandomMathFormula();
private:
    static CNode* generateRandomLeaf();
    static CNode* generateRandomInternalNode();
    static const char ca_variables[]; //ca = char array
    static const char ca_two_arguments_operators[];

};


#endif //TREEMATH_RANDOMNODEGENERATOR_H
