#ifndef TREEMATH_RANDOMNODEGENERATOR_H
#define TREEMATH_RANDOMNODEGENERATOR_H
#define RANDOM_CHOICE_GENERATE_LEAF 1
#define RANDOM_CHOICE_GET_VARIABLE 2
#define RANDOM_CHOICE_GET_NUMBER 3
#define TWO_ARGUMENTS_OPERATOR_ARRAY_SIZE 4
#define RANDOM_MAX_GENERATE_NUMBER 20
#define ALPHABET_SIZE 26

#include "CNode.h"

class RandomNodeGenerator {
public:
    static CNode* generateRandomTree();
private:
    static void generateRandomLeaf(CNode* node);
    static void generateRandomNodes(CNode* node);
    static const char ca_variables[]; //ca = char array
    static const char ca_two_arguments_operators[];
    static void setRootDataToOperator(CNode* root);
};


#endif //TREEMATH_RANDOMNODEGENERATOR_H
