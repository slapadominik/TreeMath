#include <iostream>
#include <algorithm>
#include <cmath>
#include "CTree.h"
#include "WrongVariablesValuesAmountException.h"
#include "EmptyTreeException.h"
#include "StringUtils.h"

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
        if (variables.size()==variablesValues.size()){
            return dCalculateValue(root,variablesValues);
        }
        throw WrongVariablesValuesAmountException(MSG_VARIABLES_VALUES_AMOUNT_NOT_EQUALS_VARIABLES_AMOUNT);
    }
    throw EmptyTreeException(MSG_TREE_EMPTY);
}

void CTree::vPrintVariables() {
    std::cout<<"Variables in the tree: ";
    if (variables.empty()){
        std::cout<<" none"<<std::endl;
    }
    for (int i=0; i<variables.size();i++){
        std::cout<<variables.at(i)<<" ";
    }
    std::cout<<std::endl;
}

void CTree::vJoinTree(CTree &treeToJoin) {
    //if leaf is NULL (which means that root is NULL) then copy root from treeToJoin, else find leaf and his parent and join tree
    if (!getLeaf()) {
        root = new CNode(*treeToJoin.root);
        v_copy_vars_to_existing_tree(treeToJoin);
    }
    else{
        CNode *rootCopy;
        rootCopy= new CNode(*treeToJoin.root);
        CNode *parentPrimaryTree = getLeaf()->parent;
        //check if replacing child's data of parentPrimaryTree is variable, if it is then delete this variable from vars vector
        if (StringUtils::bIsVariable(parentPrimaryTree->child_nodes.at(FIRST_OPERAND)->s_data)){
            int var_offset = i_get_variable_offset(parentPrimaryTree->child_nodes.at(FIRST_OPERAND)->s_data);
            variables.erase(variables.begin()+var_offset);
        }
        parentPrimaryTree->bReplaceChild(FIRST_OPERAND, rootCopy);
        rootCopy->parent = parentPrimaryTree;
        v_copy_vars_to_existing_tree(treeToJoin);
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
    v_copy_vars_to_existing_tree(tree);
}

CTree CTree::operator+(CTree &tree) {
    CTree sumOfTrees(*this);
    sumOfTrees.v_copy_vars_to_existing_tree(*this);
    sumOfTrees.vJoinTree(tree);
    return sumOfTrees;
}

bool CTree::b_is_formula_correct(std::string &formula) {
    std::vector<std::string> formula_splitted = split(formula,' ');
    int i_nodes_counter = 1;
    for (int i=0; i<formula_splitted.size();i++){
        if (StringUtils::bIsTwoArgumentsOperator(formula_splitted.at(i))){
            i_nodes_counter+=2;
        }
        else if (StringUtils::bIsOneArgumentOperator(formula_splitted.at(i))){
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
    vCreateNodes(root,formula_splitted, offset);
    delete offset;
    if (!b_is_formula_correct(sFormula)){
        return ERROR_CODE_INCORRECT_FORMULA_REPAIRED_TREE;
    }
    return INFO_CODE_SUCCES_BUILDING_TREE_FROM_FORMULA;
}

int CTree::iGetNodesAmountInTree() {
    int *piCounter = new int(0);
    root->iGetNodeChildrenAmount(piCounter);
    int temp = *piCounter;
    delete piCounter;
    return temp;
}

int CTree::iGetRandomNodeNumberFromTree() {
    int randomNumber = rand() % iGetNodesAmountInTree() + 1;
    return randomNumber;
}

void CTree::vCreateNodes(CNode *node, std::vector<std::string> formulaSplitted, int *iOffset) {
    if (*iOffset<formulaSplitted.size()){
        if (StringUtils::bIsTwoArgumentsOperator(formulaSplitted.at(*iOffset))){
            node->vSetDataAndCreateChildNodesAndSetParent(formulaSplitted.at(*iOffset), 2);
            *iOffset=*iOffset+1;
            vCreateNodes(node->child_nodes.at(0),formulaSplitted, iOffset);
            *iOffset=*iOffset+1;
            vCreateNodes(node->child_nodes.at(1),formulaSplitted, iOffset);
        }
        else if (StringUtils::bIsOneArgumentOperator(formulaSplitted.at(*iOffset))) {
            node->vSetDataAndCreateChildNodesAndSetParent(formulaSplitted.at(*iOffset), 1);
            *iOffset=*iOffset+1;
            vCreateNodes(node->child_nodes.at(0),formulaSplitted, iOffset);
        }
        else if (StringUtils::bIsNumber(formulaSplitted.at(*iOffset))){
            node->vSetData(formulaSplitted.at(*iOffset));
        }
        else if (StringUtils::bIsVariable(formulaSplitted.at(*iOffset))){
            node->vSetData(formulaSplitted.at(*iOffset));
            if (!b_is_element_present_in_variables_vector(node->sGetData())){
                variables.push_back(node->sGetData());
            }
        }
    }
    else{
        if (node->bIsNodeEmpty()){
            node->vSetData("1");
        }
    }

}

bool CTree::b_is_element_present_in_variables_vector(std::string element) {
    return std::find(variables.begin(), variables.end(), element) != variables.end();
}

void CTree::vClearVariables() {
    variables.clear();
}

int CTree::i_get_variable_offset(const std::string &s) {
    int i_offset=-1;
    for (int i=0; i<variables.size() && i_offset<0;i++){
        if (s==variables.at(i)){
            i_offset=i;
        }
    }
    return i_offset;
}


double CTree::dCalculateValue(CNode* node, std::vector<double> variablesValues) {
    if (StringUtils::bIsTwoArgumentsOperator(node->sGetData())){
        if (node->sGetData()=="+"){
            return dCalculateValue(node->child_nodes.at(0), variablesValues) +
                   dCalculateValue(node->child_nodes.at(1),variablesValues);
        }
        if (node->sGetData()=="-"){
            return dCalculateValue(node->child_nodes.at(0), variablesValues) -
                   dCalculateValue(node->child_nodes.at(1),variablesValues);
        }
        if (node->sGetData()=="*"){
            return dCalculateValue(node->child_nodes.at(0), variablesValues) *
                   dCalculateValue(node->child_nodes.at(1),variablesValues);
        }
        if (node->sGetData()=="/"){
            return dCalculateValue(node->child_nodes.at(0), variablesValues) /
                   dCalculateValue(node->child_nodes.at(1),variablesValues);
        }
    }
    if (StringUtils::bIsOneArgumentOperator(node->sGetData())){
        if (node->sGetData()=="sin"){
            return sin(dCalculateValue(node->child_nodes.at(0),variablesValues));
        }
        if (node->sGetData()=="cos"){
            return cos(dCalculateValue(node->child_nodes.at(0),variablesValues));
        }
    }
    if (StringUtils::bIsNumber(node->sGetData())){
        return std::stod(node->sGetData());
    }
    if (StringUtils::bIsVariable(node->sGetData())){
        return variablesValues.at(i_get_variable_offset(node->sGetData()));
    }
}

void CTree::v_copy_vars_to_existing_tree(const CTree &copyFromTree) {
    for (int i=0; i<copyFromTree.variables.size();i++){
        //if variable exists in destination tree then don't copy, otherwise copy this var
        if (i_get_variable_offset(copyFromTree.variables.at(i))<0){
            variables.push_back(copyFromTree.variables.at(i));
        }
    }
}




