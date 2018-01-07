#include <string>
#include <vector>
#include "CNode.h"

#define MSG_VARIABLES_VALUES_AMOUNT_NOT_EQUALS_VARIABLES_AMOUNT "Niepoprawna ilosc wartosci w stosunku do zmiennych znajdujacych sie w formule!"
#define MSG_TREE_EMPTY "Drzewo jest puste, nie wpisano zadnej formuly!"
#define INFO_CODE_SUCCES_BUILDING_TREE_FROM_FORMULA 4001
#define ERROR_CODE_INCORRECT_FORMULA_REPAIRED_TREE 4002
#define FIRST_OPERAND 0
#define SECOND_OPERAND 1

#ifndef TREEMATH_CTREE_H
#define TREEMATH_CTREE_H

class CTree {
    friend class RandomTreeGenerator;
public:
    CTree();
    CTree(std::string name);
    CTree(CTree &toCopy);
    CTree(CNode *toCopy);
    ~CTree();

    void operator=(const CTree &tree);
    CTree operator+(CTree &tree);
    bool operator<(CTree &tree);
    void vJoinTree(CTree &treeToJoin);
    bool bPrintTree();
    bool bClearTree();
    bool b_is_formula_correct(std::string &formula);
    int iBuildTree(std::string &sFormula);
    double dCalculateTreeValue(std::vector<double> variablesValues);
    CNode* getLeaf();
    CNode* getRoot();
    int iGetNodesAmountInTree();
    bool hasVariables(int iAmount);
    int iGetRandomNodeNumberFromTree();
    void vCreateNodes(CNode *node, std::vector<std::string> formulaSplitted, int *iOffset);
    void vClearVariables();
    void vPrintVariables();
    int i_get_variable_offset(const std::string &s);
    double dCalculateValue(CNode* node, std::vector<double> variablesValues);
    CNode* randomSubtree(int *whichChild);
    void joinSubtree(CTree *subtree);
    void vMutation();
    std::vector<CTree*> vtCrossbreed(CTree *tree);
    void setAccuracyRate(double iAccuracyRate);
    double getAccuracyRate();

private:
    std::string s_name;
    CNode *root;
    std::vector<std::string> variables;
    double accuracy_rate;
    static int objectsCreated;

    std::vector<std::string> split(std::string &stringToSplit, char regnex);
    bool b_is_element_present_in_variables_vector(std::string element);
    void v_copy_vars_to_existing_tree(const CTree &copyFromTree);
    void v_push_vars_to_vector_based_on_node(CNode *node);
};


#endif //TREEMATH_CTREE_H
