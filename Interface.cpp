#include <iostream>
#include <sstream>
#include "Interface.h"
#include "WrongVariablesValuesAmountException.h"
#include "RandomNodeGenerator.h"


Interface::Interface() {
    pc_tree = new CTree();
}

Interface::~Interface() {
    delete pc_tree;
}

bool Interface::b_is_number(const std::string &s) {
    std::istringstream iss(s);
    double d;
    return iss >> d >> std::ws && iss.eof();
}

std::vector<std::string> Interface::split(std::string sStringToSplit, char chRegnex) {
    std::string accumulator = "";
    std::vector<std::string> splited;
    for (int i = 0; i < sStringToSplit.size(); ++i)
        if (sStringToSplit[i] != chRegnex)
            accumulator += sStringToSplit[i];
        else if (accumulator.size() != 0) {
            splited.push_back(accumulator);
            accumulator = "";
        }
    splited.push_back(accumulator);
    return splited;
}

void Interface::vRunApp() {
    std::string s_command;
    std::string s_command_param0="";
    std::cout<<MSG_START_PROGRAM<<std::endl;
    while (s_command_param0!="exit") {
        getline(std::cin, s_command);
        std::vector<std::string> c_command_splitted = split(s_command, ' ');
        s_command_param0 = c_command_splitted[0];

        if (s_command_param0=="enter"){
            std::string formula_substring = s_command.substr(5);
            pc_tree->vClearVariables();
            if (pc_tree->iBuildTree(formula_substring)==ERROR_CODE_INCORRECT_FORMULA_REPAIRED_TREE){
                std::cout<<ERROR_MSG_INCORRECT_FORMULA_REPAIRED_TREE<<std::endl;
            }
            pc_tree->bPrintTree();
        }
        else if (s_command_param0=="vars"){
            pc_tree->vPrintVariables();
        }
        else if (s_command_param0=="print"){
            pc_tree->bPrintTree();
        }
        else if (s_command_param0=="comp"){
            bool params_are_numbers = true;
            for (int i=1; i<c_command_splitted.size() && params_are_numbers;i++){
                if (!b_is_number(c_command_splitted[i])){
                    params_are_numbers = false;
                }
            }
            if (params_are_numbers){
                std::vector<double> variableValues;
                for (int i=1;i<c_command_splitted.size();i++){
                    variableValues.push_back(std::stod(c_command_splitted[i]));
                }
                double result = 0;
                try{
                    result = pc_tree->dCalculateTreeValue(variableValues);
                    std::cout<<"Wartosc formuly = "<<result<<std::endl;
                } catch (WrongVariablesValuesAmountException &exception){
                    std::cout<<exception.getMessage()<<std::endl;
                }
            }
            else{
                std::cout<<ERROR_MSG_PARAMS_ARENT_NUMBERS<<std::endl;
            }
        }
        else if (s_command_param0=="join") {
            std::string formula_substring = s_command.substr(4);
            CTree treeToAdd;
            CTree *result;
            result = new CTree();
            if (treeToAdd.iBuildTree(formula_substring) == ERROR_CODE_INCORRECT_FORMULA_REPAIRED_TREE) {
                std::cout << ERROR_MSG_INCORRECT_FORMULA_REPAIRED_TREE << std::endl;
            }
            treeToAdd.bPrintTree();
            *result = *pc_tree + treeToAdd;
            delete pc_tree;
            pc_tree = result;
            std::cout << "Pomyslnie polaczono drzewa." << std::endl;
        }
        else if (s_command_param0!="exit"){
            std::cout<<"Bledna komenda"<<std::endl;
        }
    }
}


