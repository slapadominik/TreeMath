#include <time.h>
#include <iostream>
#include "RandomNodeGenerator.h"
#include "StringUtils.h"

const char RandomNodeGenerator::ca_variables[] = {'a','b','c','d','e','f','g','h','i','j','k', 'l', 'm', 'n', 'o', 'p','q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
const char RandomNodeGenerator::ca_two_arguments_operators[] = {'+','-','*','/'};
const std::string RandomNodeGenerator::ca_one_argument_operators[] = {"sin", "cos"};


CNode* RandomNodeGenerator::generateRandomTree() {
    CNode* root = new CNode();
    srand(time(NULL));
    int i_random_choice = rand()%2;
    std::cout<<"GenerateRandomTree random_num: "<<i_random_choice<<std::endl;
    if (i_random_choice==RANDOM_CHOICE_GENERATE_LEAF){
        generateRandomLeaf(root);
    }
    else{ //RANDOM_CHOICE_GENERATE_NODES
        setRootDataToOperator(root);
        generateRandomNodes(root);
    }
    return root;
}

void RandomNodeGenerator::generateRandomLeaf(CNode *node) {
    int i_random_variables_or_numbers = rand()%2+2;
    std::cout<<"GenerateRandomLeaf random_num: "<<i_random_variables_or_numbers<<std::endl;
    if (i_random_variables_or_numbers==RANDOM_CHOICE_GET_NUMBER){
        int i_random_number = rand()%RANDOM_MAX_GENERATE_NUMBER;
        std::cout<<i_random_number<<std::endl;
        std::string s_random_number = StringUtils::intToString(i_random_number);
        node->vSetDataAndCreateChildNodesAndSetParent(s_random_number, 0);
    }
    else { //RANDOM_CHOICE_GET_VARIABLE
        int i_random_letter = rand()%ALPHABET_SIZE;
        std::string s_random_letter = StringUtils::charToString(ca_variables[i_random_letter]);
        node->vSetDataAndCreateChildNodesAndSetParent(s_random_letter, 0);
    }

}

void RandomNodeGenerator::generateRandomNodes(CNode *node) {
    if (StringUtils::bIsTwoArgumentsOperator(node->sGetData())){
        node->vCreateChildNodes(2);
        node->getChild(0)->vSetData(generateRandomDataForNode());
        generateRandomNodes(node->getChild(0));
        node->getChild(1)->vSetData(generateRandomDataForNode());
        generateRandomNodes(node->getChild(1));
    }
    else if (StringUtils::bIsOneArgumentOperator(node->sGetData())){
        node->vCreateChildNodes(1);
        node->getChild(0)->vSetData(generateRandomDataForNode());
        generateRandomNodes(node->getChild(0));
    }
}

void RandomNodeGenerator::setRootDataToOperator(CNode *root) {
    int i_random_choice_two_arguments_operator = rand()%TWO_ARGUMENTS_OPERATOR_ARRAY_SIZE;
    std::string random_operator = StringUtils::charToString(ca_two_arguments_operators[i_random_choice_two_arguments_operator]);
    root->vSetData(random_operator);
}

std::string RandomNodeGenerator::generateRandomDataForNode() {
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
    else if(i_random_data_type==RANDOM_CHOICE_GET_VARIABLE){
        data = getRandomVariable();
    }
    return data;
}

std::string RandomNodeGenerator::getRandomNumber(int maxNumber) {
    int i_random_number = rand()%maxNumber;
    std::string number = StringUtils::intToString(i_random_number);
    return number;
}

std::string RandomNodeGenerator::getRandomTwoArgumentOperator() {
    int i_random_choice_two_arguments_operator = rand()%TWO_ARGUMENTS_OPERATOR_ARRAY_SIZE;
    std::string random_operator = StringUtils::charToString(ca_two_arguments_operators[i_random_choice_two_arguments_operator]);
    return random_operator;
}

std::string RandomNodeGenerator::getRandomOneArgumentOperator() {
    int i_random_choice_one_argument_operator = rand()%ONE_ARGUMENT_OPERATOR_ARRAY_SIZE;
    return ca_one_argument_operators[i_random_choice_one_argument_operator];
}

std::string RandomNodeGenerator::getRandomVariable(){
    int i_random_choice_variable = rand()%ALPHABET_SIZE;
    std::string random_variable = StringUtils::charToString(ca_variables[i_random_choice_variable]);
    return random_variable;
}


