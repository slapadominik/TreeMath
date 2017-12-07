#include <string>
#include <vector>
#ifndef TREEMATH_CNODE_H
#define TREEMATH_CNODE_H

#define FIRST_OPERAND 0
#define SECOND_OPERAND 1

class CNode {
    friend class CTree;
public:
    CNode();
    CNode(std::string sData);
    CNode(CNode &toCopy);
    ~CNode();

    std::string toString();
    void vSetDataAndCreateChildNodesAndSetParent(std::string &sData, int iAmountOfNodes);
    void vCreateNodes(std::vector<std::string> formulaSplitted, int *iOffset);
    void vPrintNodes();
    void vPrintVariables();
    void vRemoveChildren();
    void vClearVariables();
    void vAddChild(CNode *nodeToAdd);
    bool bRemoveChild(int iOffset);
    bool bIsLeaf();
    bool bIsDataEmpty();
    bool bReplaceChild(int iOffset, CNode *newChild);
    double dCalculateValue(std::vector<double> variablesValues);
    int* iGetNodeChildrenAmount(int *piCounter);
    CNode* nGetLeaf();

private:
    std::string s_data;
    std::vector<CNode*> child_nodes;
    CNode *parent;

    bool b_is_element_present_in_variables_vector(std::string element);
    int i_get_variable_offset(const std::string &s);
    static std::vector<std::string> variables;
};



#endif //TREEMATH_CNODE_H
