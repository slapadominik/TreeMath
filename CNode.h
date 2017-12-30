#include <string>
#include <vector>
#ifndef TREEMATH_CNODE_H
#define TREEMATH_CNODE_H

#define FIRST_OPERAND 0
#define SECOND_OPERAND 1

class CNode {
    friend class CTree;
    friend class RandomNodeGenerator;
public:
    CNode();
    CNode(std::string sData);
    CNode(CNode &toCopy);
    ~CNode();

    std::string toString();
    void vSetDataAndCreateChildNodesAndSetParent(std::string &sData, int iAmountOfNodes);
    void vCreateChildNodes(int iAmountOfChildren);
    void vPrintNodes();
    void vRemoveChildren();
    void vSetData(std::string sData);
    void vAddChild(CNode *nodeToAdd);
    bool bRemoveChild(int iOffset);
    bool bIsLeaf();
    bool bIsNodeEmpty();
    bool bReplaceChild(int iOffset, CNode *newChild);
    int* iGetNodeChildrenAmount(int *piCounter);
    std::string sGetData();
    CNode* nGetLeaf();
    CNode* getChild(int iChildOffset);
    bool hasChildrenAmount(int childrenAmount);
    void vSetEmptyData();

private:
    std::string s_data;
    std::vector<CNode*> child_nodes;
    CNode *parent;
};



#endif //TREEMATH_CNODE_H
