#include <algorithm>
#include <cmath>
#include <iostream>
#include "CNode.h"
#include "StringUtils.h"

#include <sstream>


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


void CNode::vPrintNodes() {
    std::cout<<toString()<<" ";
    for (int i=0;i<child_nodes.size();i++){
        child_nodes.at(i)->vPrintNodes();
    }
}


CNode* CNode::nGetLeaf() {
    if (bIsLeaf()){
        return this;
    }
    //if it is not leaf (leaf is variable or number value) then it is operator, so we takes FIRST_OPERAND, which means first child of operator
    return child_nodes.at(FIRST_OPERAND)->nGetLeaf();
}

bool CNode::bIsLeaf() {
    return (StringUtils::bIsNumber(s_data) || StringUtils::bIsVariable(s_data));
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

bool CNode::bIsNodeEmpty() {
    return s_data=="root";
}

bool CNode::bReplaceChild(int iOffset, CNode *newChild) {
    if (iOffset<child_nodes.size()){
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

void CNode::vSetData(std::string sData) {
    s_data = sData;
}

std::string CNode::sGetData() {
    return s_data;
}

void CNode::vCreateChildNodes(int iAmountOfChildren) {
    for (int i=0; i<iAmountOfChildren;i++){
        child_nodes.push_back(new CNode());
        child_nodes.at(i)->parent=this;
    }
}

CNode *CNode::getChild(int iChildOffset) {
    if (iChildOffset<child_nodes.size()){
        return child_nodes.at(iChildOffset);
    }
    return NULL;
}














