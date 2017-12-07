#include <algorithm>
#include <iostream>
#include "CNode.h"
#include "StringValidator.h"
#include <cmath>
#include <sstream>

std::vector<std::string> CNode::variables;

CNode::CNode() {
    s_data = "root";
    parent = NULL;
}

CNode::CNode(std::string sData) {
    s_data=sData;
}


CNode::CNode(CNode &toCopy) {
    s_data=toCopy.s_data;
    for (int i=0; i<toCopy.child_nodes.size();i++){
        child_nodes.push_back(new CNode(*toCopy.child_nodes.at(i)));
        child_nodes.at(i)->parent=this;
    }
}

CNode::~CNode() {
    vRemoveChildren();
}


std::string CNode::toString() {
    return s_data;
}

void CNode::vSetDataAndCreateChildNodesAndSetParent(std::string &sData, int iAmountOfNodes) {
    s_data=sData;
    for (int i=0; i<iAmountOfNodes;i++){
        child_nodes.push_back(new CNode());
        child_nodes.at(i)->parent=this;
    }

}

void CNode::vCreateNodes(std::vector<std::string> formulaSplitted, int *iOffset) {
    if (*iOffset<formulaSplitted.size()){
        if (StringValidator::bIsTwoArgumentsOperator(formulaSplitted.at(*iOffset))){
            vSetDataAndCreateChildNodesAndSetParent(formulaSplitted.at(*iOffset), 2);
            *iOffset=*iOffset+1;
            child_nodes.at(0)->vCreateNodes(formulaSplitted, iOffset);
            *iOffset=*iOffset+1;
            child_nodes.at(1)->vCreateNodes(formulaSplitted, iOffset);
        }
        else if (StringValidator::bIsOneArgumentOperator(formulaSplitted.at(*iOffset))) {
            vSetDataAndCreateChildNodesAndSetParent(formulaSplitted.at(*iOffset), 1);
            *iOffset=*iOffset+1;
            child_nodes.at(0)->vCreateNodes(formulaSplitted, iOffset);
        }
        else if (StringValidator::bIsNumber(formulaSplitted.at(*iOffset))){
            s_data=formulaSplitted.at(*iOffset);
        }
        else if (StringValidator::bIsVariable(formulaSplitted.at(*iOffset))){
            s_data=formulaSplitted.at(*iOffset);
            if (!b_is_element_present_in_variables_vector(s_data)){
                variables.push_back(s_data);
            }
        }
    }
    else{
        if (bIsDataEmpty()){
            s_data="1";
        }
        else{
            std::cout<<"Kutang"<<std::endl;
        }
    }

}


void CNode::vPrintNodes() {
    std::cout<<toString()<<" ";
    for (int i=0;i<child_nodes.size();i++){
        child_nodes.at(i)->vPrintNodes();
    }
}



void CNode::vPrintVariables() {
    std::cout<<"Variables in the tree: ";
    if (variables.empty()){
        std::cout<<" none"<<std::endl;
    }
    for (int i=0; i<variables.size();i++){
        std::cout<<variables.at(i)<<" ";
    }
    std::cout<<std::endl;
}


double CNode::dCalculateValue(std::vector<double> variablesValues) {
    if (StringValidator::bIsTwoArgumentsOperator(s_data)){
        if (s_data=="+"){
            return child_nodes.at(0)->dCalculateValue(variablesValues) +
                    child_nodes.at(1)->dCalculateValue(variablesValues);
        }
        if (s_data=="-"){
            return child_nodes.at(0)->dCalculateValue(variablesValues) -
                    child_nodes.at(1)->dCalculateValue(variablesValues);
        }
        if (s_data=="*"){
            return child_nodes.at(0)->dCalculateValue(variablesValues) *
                    child_nodes.at(1)->dCalculateValue(variablesValues);
        }
        if (s_data=="/"){
            return child_nodes.at(0)->dCalculateValue(variablesValues) /
                    child_nodes.at(1)->dCalculateValue(variablesValues);
        }
    }
    if (StringValidator::bIsOneArgumentOperator(s_data)){
        if (s_data=="sin"){
            return sin(child_nodes.at(0)->dCalculateValue(variablesValues));
        }
        if (s_data=="cos"){
            return cos(child_nodes.at(0)->dCalculateValue(variablesValues));
        }
    }
    if (StringValidator::bIsNumber(s_data)){
        return std::stod(s_data);
    }
    if (StringValidator::bIsVariable(s_data)){
        return variablesValues.at(i_get_variable_offset(s_data));
    }
}

bool CNode::b_is_element_present_in_variables_vector(std::string element) {
    return (std::find(variables.begin(), variables.end(), element) != variables.end());
}

int CNode::i_get_variable_offset(const std::string &s) {
    int i_offset=-1;
    for (int i=0; i<variables.size() && i_offset<0;i++){
        if (s==variables.at(i)){
            i_offset=i;
        }
    }
    return i_offset;
}

CNode* CNode::nGetLeaf() {
    if (bIsLeaf()){
        return this;
    }
    //if it is not leaf (leaf is variable or number value) then it is operator, so we takes FIRST_OPERAND, which means first child of operator
    return child_nodes.at(FIRST_OPERAND)->nGetLeaf();
}

bool CNode::bIsLeaf() {
    return (StringValidator::bIsNumber(s_data) || StringValidator::bIsVariable(s_data));
}

void CNode::vRemoveChildren() {
    for (int i=0; i<child_nodes.size();i++){
        delete child_nodes.at(i);
    }
    child_nodes.clear();
}

void CNode::vAddChild(CNode *nodeToAdd) {
    child_nodes.push_back(nodeToAdd);
}

bool CNode::bRemoveChild(int iOffset) {
    if (iOffset<child_nodes.size()){
        delete child_nodes.at(iOffset);
        child_nodes.erase(child_nodes.begin()+iOffset);
        return true;
    }
    return false;
}

bool CNode::bIsDataEmpty() {
    return s_data=="root";
}

void CNode::vClearVariables() {
    variables.clear();
}

bool CNode::bReplaceChild(int iOffset, CNode *newChild) {
    if (iOffset<child_nodes.size()){
        if (StringValidator::bIsVariable(child_nodes.at(iOffset)->s_data)){
            int var_offset = i_get_variable_offset(child_nodes.at(iOffset)->s_data);
            variables.erase(variables.begin()+var_offset);
        }
        delete child_nodes[iOffset];
        child_nodes[iOffset]=newChild;
        return true;
    }
    return false;
}

int* CNode::iGetNodeChildrenAmount(int *piCounter) {
    *piCounter+=1;
    for (int i=0;i<child_nodes.size();i++){
        child_nodes.at(i)->iGetNodeChildrenAmount(piCounter);
    }
    return piCounter;
}














