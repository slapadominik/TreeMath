#include <algorithm>
#include <cmath>
#include <iostream>
#include "CNode.h"
#include "StringUtils.h"

#include <sstream>
#include <time.h>


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
    if (child_nodes.size()==1){
        return child_nodes.at(0)->nGetLeaf();
    }
    if (child_nodes.size()==2){
        srand(time(NULL));
        int random_child = rand()%2;
        if (random_child==0){
            return child_nodes.at(0)->nGetLeaf();
        }
        else{
            return child_nodes.at(1)->nGetLeaf();
        }
    }
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

bool CNode::hasChildrenAmount(int childrenAmount) {
    return child_nodes.size()==childrenAmount;
}

void CNode::vSetEmptyData() {
    s_data = "root";
}














