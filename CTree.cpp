#include <iostream>
#include "CTree.h"
#include "WrongVariablesValuesAmountException.h"
#include "EmptyTreeException.h"
#include "StringValidator.h"

CTree::CTree() {
    s_name="def_name";
    root = new CNode();
}

CTree::CTree(std::string sName) {
    s_name=sName;
    root = new CNode();
}

CTree::CTree(CTree &toCopy) {
    s_name = toCopy.s_name+"_copy";
    root = new CNode(*toCopy.root);
}

CTree::~CTree() {
    bClearTree();
}

bool CTree::bPrintTree(){
    if (root){
        std::cout<<"Tree: ";
        root->vPrintNodes();
        std::cout<<std::endl;
        return true;
    }
    return false;
}

bool CTree::bClearTree() {
    if (root){
        for (int i=0; i<root->child_nodes.size();i++){
            delete root->child_nodes.at(i);
        }
        root->child_nodes.clear();
        delete root;
        root = NULL;
        return true;
    }
    return false;
}


std::vector<std::string> CTree::split(std::string &stringToSplit, char regnex){
    std::string accumulator = "";
    std::vector<std::string> splited;
    for (int i = 0; i < stringToSplit.size(); ++i)
        if (stringToSplit[i] != regnex)
            accumulator += stringToSplit[i];
        else if (accumulator.size() != 0) {
            splited.push_back(accumulator);
            accumulator = "";
        }
    splited.push_back(accumulator);
    return splited;
}

double CTree::dCalculateTreeValue(std::vector<double> variablesValues) {
    if (root){
        if (root->variables.size()==variablesValues.size()){
            return root->dCalculateValue(variablesValues);
        }
        throw WrongVariablesValuesAmountException(MSG_VARIABLES_VALUES_AMOUNT_NOT_EQUALS_VARIABLES_AMOUNT);
    }
    throw EmptyTreeException(MSG_TREE_EMPTY);
}

void CTree::vPrintVariables() {
    root->vPrintVariables();
}

void CTree::vJoinTree(CTree &treeToJoin) {
    //if leaf is NULL (which means that root is NULL) then copy root from treeToJoin, else find leaf and his parent and join tree
    if (!getLeaf()) {
        root = new CNode(*treeToJoin.root);
    }
    else{
        CNode *rootCopy;
        rootCopy= new CNode(*treeToJoin.root);
        CNode *parentPrimaryTree = getLeaf()->parent;
        parentPrimaryTree->bReplaceChild(FIRST_OPERAND, rootCopy);
        rootCopy->parent = parentPrimaryTree;
    }

}

CNode* CTree::getLeaf() {
    if (!root){
        return NULL;
    }
    return root->nGetLeaf();
}

void CTree::operator=(const CTree &tree) {
    s_name=tree.s_name;
    root = new CNode(*tree.root);
}

CTree CTree::operator+(CTree &tree) {
    CTree sumOfTrees(*this);
    sumOfTrees.vJoinTree(tree);
    return sumOfTrees;
}

bool CTree::b_is_formula_correct(std::string &formula) {
    std::vector<std::string> formula_splitted = split(formula,' ');
    int i_nodes_counter = 1;
    for (int i=0; i<formula_splitted.size();i++){
        if (StringValidator::bIsTwoArgumentsOperator(formula_splitted.at(i))){
            i_nodes_counter+=2;
        }
        else if (StringValidator::bIsOneArgumentOperator(formula_splitted.at(i))){
            i_nodes_counter++;
        }
    }
    return i_nodes_counter==formula_splitted.size();
}


int CTree::iBuildTree(std::string &sFormula) {
    std::vector<std::string> formula_splitted = split(sFormula,' ');
    int *offset = new int();
    *offset = 0;
    if (root) {
        delete root;
    }
    root = new CNode();
    root->vCreateNodes(formula_splitted, offset);
    delete offset;
    if (!b_is_formula_correct(sFormula)){
        return ERROR_CODE_INCORRECT_FORMULA_REPAIRED_TREE;
    }
    return INFO_CODE_SUCCES_BUILDING_TREE_FROM_FORMULA;
}

bool CTree::bClearVariables() {
    if (root){
        root->vClearVariables();
        return true;
    }
    return false;
}

int CTree::iGetNodesAmountInTree() {
    int *piCounter = new int(0);
    root->iGetNodeChildrenAmount(piCounter);
    int temp = *piCounter;
    delete piCounter;
    return temp;
}






