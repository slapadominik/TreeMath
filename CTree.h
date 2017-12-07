#include <string>
#include <vector>
#include "CNode.h"

#define MSG_VARIABLES_VALUES_AMOUNT_NOT_EQUALS_VARIABLES_AMOUNT "Niepoprawna ilosc wartosci w stosunku do zmiennych znajdujacych sie w formule!"
#define MSG_TREE_EMPTY "Drzewo jest puste, nie wpisano zadnej formuly!"
#define INFO_CODE_SUCCES_BUILDING_TREE_FROM_FORMULA 4001
#define ERROR_CODE_INCORRECT_FORMULA_REPAIRED_TREE 4002

#ifndef TREEMATH_CTREE_H
#define TREEMATH_CTREE_H


class CTree {
public:
    CTree();
    CTree(std::string name);
    CTree(CTree &toCopy);
    ~CTree();

    void operator=(const CTree &tree);
    CTree operator+(CTree &tree);

    void vPrintVariables();
    void vJoinTree(CTree &treeToJoin);
    bool bClearVariables();
    bool bPrintTree();
    bool bClearTree();
    bool b_is_formula_correct(std::string &formula);
    int iBuildTree(std::string &sFormula);
    double dCalculateTreeValue(std::vector<double> variablesValues);
    CNode* getLeaf();

private:
    std::string s_name;
    CNode *root;
    std::vector<std::string> split(std::string &stringToSplit, char regnex);

};


#endif //TREEMATH_CTREE_H
