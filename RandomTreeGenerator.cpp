#include <time.h>
#include <iostream>
#include "RandomTreeGenerator.h"
#include "StringUtils.h"

const char RandomTreeGenerator::ca_variables[] = {'x', 'y'};
const char RandomTreeGenerator::ca_two_arguments_operators[] = {'+','-','*','/'};
const std::string RandomTreeGenerator::ca_one_argument_operators[] = {"sin", "cos"};


CTree* RandomTreeGenerator::generateRandomTree() {
    CTree* tree;
    tree = new CTree();
    CNode* root = tree->getRoot();
    setRootDataToOperator(root);
    generateRandomNodes(root, tree);

    return tree;
}

void RandomTreeGenerator::generateRandomLeaf(CTree *tree) {
    CNode *node = tree->getRoot();
    int i_random_variables_or_numbers = rand()%2+2;
    if (i_random_variables_or_numbers==RANDOM_CHOICE_GET_NUMBER){
        int i_random_number = rand()%RANDOM_MAX_GENERATE_NUMBER;
        std::string s_random_number = StringUtils::intToString(i_random_number);
        node->vSetDataAndCreateChildNodesAndSetParent(s_random_number, 0);

    }
    else { //RANDOM_CHOICE_GET_VARIABLE
        int i_random_letter = rand()%ALPHABET_SIZE;
        std::string s_random_letter = StringUtils::charToString(ca_variables[i_random_letter]);
        node->vSetDataAndCreateChildNodesAndSetParent(s_random_letter, 0);
        tree->variables.push_back(s_random_letter);
    }

}

void RandomTreeGenerator::generateRandomNodes(CNode *node,CTree *workingTree) {
    if (StringUtils::bIsTwoArgumentsOperator(node->sGetData())){
        node->vCreateChildNodes(2);
        node->getChild(0)->vSetData(generateRandomDataForNode());
        generateRandomNodes(node->getChild(0), workingTree);
        node->getChild(1)->vSetData(generateRandomDataForNode());
        generateRandomNodes(node->getChild(1),workingTree);
    }
    else if (StringUtils::bIsOneArgumentOperator(node->sGetData())){
        node->vCreateChildNodes(1);
        node->getChild(0)->vSetData(generateRandomDataForNode());
        generateRandomNodes(node->getChild(0),workingTree);
    }
    else if (StringUtils::bIsVariable(node->sGetData())){
        if (!workingTree->b_is_element_present_in_variables_vector(node->sGetData())){
                workingTree->variables.push_back(node->sGetData());
        }
    }
}

void RandomTreeGenerator::setRootDataToOperator(CNode *root) {
    int i_random_choice_two_arguments_operator = rand()%TWO_ARGUMENTS_OPERATOR_ARRAY_SIZE;
    std::string random_operator = StringUtils::charToString(ca_two_arguments_operators[i_random_choice_two_arguments_operator]);
    root->vSetData(random_operator);
}

std::string RandomTreeGenerator::generateRandomDataForNode() {
    std::string data;
    int i_random_data_type = rand()%4;
    if (i_random_data_type==RANDOM_CHOICE_GET_TWO_ARGUMENTS_OPERATOR){
        data = getRandomTwoArgumentOperator();
    }
    else if(i_random_data_type==RANDOM_CHOICE_GET_ONE_ARGUMENT_OPERATOR){
        data = getRandomOneArgumentOperator();
    }
    else if(i_random_data_type==RANDOM_CHOICE_GET_NUMBER){
        data = getRandomNumber(20);
    }
    else if (i_random_data_type==RANDOM_CHOICE_GET_VARIABLE){
            data = getRandomVariable();
    }

    return data;
}

std::string RandomTreeGenerator::getRandomNumber(int maxNumber) {
    int i_random_number = rand()%maxNumber+1;
    std::string number = StringUtils::intToString(i_random_number);
    return number;
}

std::string RandomTreeGenerator::getRandomTwoArgumentOperator() {
    int i_random_choice_two_arguments_operator = rand()%TWO_ARGUMENTS_OPERATOR_ARRAY_SIZE;
    std::string random_operator = StringUtils::charToString(ca_two_arguments_operators[i_random_choice_two_arguments_operator]);
    return random_operator;
}

std::string RandomTreeGenerator::getRandomOneArgumentOperator() {
    int i_random_choice_one_argument_operator = rand()%ONE_ARGUMENT_OPERATOR_ARRAY_SIZE;
    return ca_one_argument_operators[i_random_choice_one_argument_operator];
}

std::string RandomTreeGenerator::getRandomVariable(){
    int i_random_choice_variable = rand()%ALPHABET_SIZE;
    std::string random_variable = StringUtils::charToString(ca_variables[i_random_choice_variable]);
    return random_variable;
}

CNode* RandomTreeGenerator::generateRandomTreeOrLeaf() {
    CTree* tree;
    tree = new CTree();
    int i_rand_choice = rand()%3;
    if (i_rand_choice==0 || i_rand_choice==1){
        generateRandomLeaf(tree);
    }
    else{
        CNode* root = tree->getRoot();
        setRootDataToOperator(root);
        generateRandomNodes(root, tree);
    }
    CNode *node = new CNode(*tree->root);
    delete tree;
    return node;
}


