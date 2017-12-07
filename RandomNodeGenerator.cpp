#include "RandomNodeGenerator.h"

const char RandomNodeGenerator::ca_variables[] = {'a','b','c','d','e','f','g','h','i','j','k'};
const char RandomNodeGenerator::ca_two_arguments_operators[] = {'+','-','*','/'};

CNode &RandomNodeGenerator::generateRandomNode() {
    int randomNumber = rand()%2;
}

CNode* RandomNodeGenerator::generateRandomLeaf() {
    CNode* pcNode;
    pcNode = new CNode();
    return pcNode;
}

CNode* RandomNodeGenerator::generateRandomInternalNode() {
    CNode *internalNode;
    internalNode = new CNode();
    return internalNode;
}

std::string RandomNodeGenerator::generateRandomMathFormula() {
    std::string formula = "";
    formula.push_back('c');
    formula.push_back(' ');
    formula.push_back('x');
    return formula;
}
