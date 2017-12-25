#ifndef TREEMATH_RANDOMNODEGENERATOR_H
#define TREEMATH_RANDOMNODEGENERATOR_H
#define RANDOM_CHOICE_GENERATE_LEAF 1
#define RANDOM_CHOICE_GET_TWO_ARGUMENTS_OPERATOR 0
#define RANDOM_CHOICE_GET_ONE_ARGUMENT_OPERATOR 1
#define RANDOM_CHOICE_GET_VARIABLE 2
#define RANDOM_CHOICE_GET_NUMBER 3
#define TWO_ARGUMENTS_OPERATOR_ARRAY_SIZE 4
#define ONE_ARGUMENT_OPERATOR_ARRAY_SIZE 2
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
    static const std::string ca_one_argument_operators[];
    static void setRootDataToOperator(CNode* root);
    static std::string generateRandomDataForNode();
    static std::string getRandomNumber(int maxNumber);
    static std::string getRandomTwoArgumentOperator();
    static std::string getRandomOneArgumentOperator();
    static std::string getRandomVariable();
};


#endif //TREEMATH_RANDOMNODEGENERATOR_H
