//
// Created by Ululula on 27.12.2017.
//

#include <iostream>
#include <time.h>
#include "GeneticProgramming.h"
#include "RandomTreeGenerator.h"
#include "FileReader.h"
#include <math.h>
#include <algorithm>

GeneticProgramming::GeneticProgramming() {
    b_is_data_initialized = false;
}

GeneticProgramming::~GeneticProgramming() {
    v_clear_beginning_population();
    v_clear_children_popualtion();
    parents_population.clear();
}


void GeneticProgramming::initializePopulation(int iTreesAmount) {
    for (int i=0; i<iTreesAmount;i++){
        beginning_population.push_back(RandomTreeGenerator::generateRandomTree());
    }
}

void GeneticProgramming::printBeginningPopulation() {
    std::cout<<"Beginning population"<<std::endl;
    for (int i=0; i<beginning_population.size();i++){
        beginning_population.at(i)->bPrintTree();
        std::cout<<beginning_population.at(i)->getAccuracyRate()<<std::endl;
    }
}


void GeneticProgramming::v_clear_beginning_population() {
    for (int i=0;i<beginning_population.size();i++){
        delete beginning_population.at(i);
    }
    beginning_population.clear();
}

void GeneticProgramming::evaluate() {
    for (int i=0;i<beginning_population.size();i++){
        double accuracy_rate = calculate_accuracy_rate_for_tree(*beginning_population.at(i));
        beginning_population.at(i)->setAccuracyRate(accuracy_rate);
    }
}

void GeneticProgramming::initializeDataFromFile(std::string fileName) {
    std::vector<std::string> text_from_file = FileReader::readFromFile(fileName);
    if (text_from_file.size()==0){
    }
    else {
        x_y_xy_values = FileReader::splitTextIntoDoubleVector(text_from_file);
        b_is_data_initialized = true;
    }
}

double GeneticProgramming::calculate_accuracy_rate_for_tree(CTree &tree) {
    double result = 0;
    std::vector<double> arguments;
    int x;
    int y;
    for (int xy=2; xy<x_y_xy_values.size();xy+=3){
        x=xy-2;
        y=xy-1;
        if (tree.hasVariables(2)){
            arguments.push_back(x_y_xy_values.at(x));
            arguments.push_back(x_y_xy_values.at(y));
        }
        else if (tree.hasVariables(1)){
            arguments.push_back(x_y_xy_values.at(y));
        }
        result+=pow(x_y_xy_values.at(xy)-tree.dCalculateTreeValue(arguments),2);
        arguments.clear();
    }
    return result;
}

void GeneticProgramming::printVectorValues() {
    for (int i=0; i<x_y_xy_values.size();i++){
        std::cout<<x_y_xy_values.at(i)<<std::endl;
    }
}

void GeneticProgramming::selection() {
    std::vector<CTree*> temp = beginning_population;

    int i_random_tree;
    while (temp.size()>0){
        i_random_tree = rand()%temp.size();
        CTree *tree1 = temp.at(i_random_tree);
        temp.erase(temp.begin()+i_random_tree);
        if (temp.size()>=1){
            i_random_tree = rand()%temp.size();
            CTree *tree2 = temp.at(i_random_tree);
            temp.erase(temp.begin()+i_random_tree);
            CTree *winner = tournament(tree1, tree2);
            parents_population.push_back(winner);
        }
    }
}

CTree *GeneticProgramming::tournament(CTree *tree1, CTree *tree2) {
    if (tree1->getAccuracyRate()>tree2->getAccuracyRate()){
        return tree2;
    }
    else{
        return tree1;
    }
}

void GeneticProgramming::printParentsPopulation() {
    if (parents_population.empty()){
        std::cout<<"Parents population: Empty"<<std::endl;
    }
    else{
        std::cout<<"Parents population:"<<std::endl;
        for (int i=0; i<parents_population.size();i++){
            parents_population.at(i)->bPrintTree();
            std::cout<<parents_population.at(i)->getAccuracyRate()<<std::endl;
        }
    }
}

void GeneticProgramming::crossbreedPairOfTrees(CTree *tree1, CTree *tree2) {
    int crossbreed_rate = 25; //25%
    int i_random_crossbreed_rate = rand()%100;
    if (i_random_crossbreed_rate<=crossbreed_rate){
        std::vector<CTree*> children = tree1->vtCrossbreed(tree2);
        children_population.push_back(children.at(0));
        children_population.push_back(children.at(1));
    }
    else{
        children_population.push_back(new CTree(*tree1));
        children_population.push_back(new CTree(*tree2));
    }
}

void GeneticProgramming::v_clear_children_popualtion() {
    for (int i=0; i<children_population.size();i++){
        delete children_population.at(i);
    }
    children_population.clear();
}

void GeneticProgramming::crossbreedParentsPopulation() {
    std::vector<CTree*> temp = parents_population;
    int i_random_tree;
    while (!temp.empty()){
        i_random_tree = rand()%temp.size();
        CTree *tree1 = temp.at(i_random_tree);
        temp.erase(temp.begin()+i_random_tree);
        if (temp.size()>=1){
            i_random_tree = rand()%temp.size();
            CTree *tree2 = temp.at(i_random_tree);
            temp.erase(temp.begin()+i_random_tree);
            crossbreedPairOfTrees(tree1, tree2);
        }
        else{
            children_population.push_back(new CTree(*tree1));
        }
    }
}

void GeneticProgramming::printChildrenPopulation() {
    if (children_population.empty()){
        std::cout<<"Children population: Empty"<<std::endl;
    }
    else{
        std::cout<<"Children population"<<std::endl;
        for (int i=0; i<children_population.size();i++){
            children_population.at(i)->bPrintTree();
            std::cout<<children_population.at(i)->getAccuracyRate()<<std::endl;
        }
    }
}

void GeneticProgramming::evaluateChildrenPopulation() {
    for (int i=0;i<children_population.size();i++){
        double accuracy_rate = calculate_accuracy_rate_for_tree(*children_population.at(i));
        children_population.at(i)->setAccuracyRate(accuracy_rate);
    }
}

void GeneticProgramming::mutation() {
    int i_mutation_rate=15;
    int i_random_mutation_rate;
    for (int i=0; i<children_population.size();i++){
        i_random_mutation_rate = rand()%100;
        if (i_random_mutation_rate<=i_mutation_rate){
            children_population.at(i)->vMutation();
        }
    }
}

void GeneticProgramming::vRunIteration() {
    if (b_is_data_initialized){
        selection();
        crossbreedParentsPopulation();
        mutation();
        evaluateChildrenPopulation();
    }
}

void GeneticProgramming::vAfterIteration() {
    v_clear_beginning_population();
    parents_population.clear();
    beginning_population = children_population;
    children_population.clear();
}

CTree* GeneticProgramming::vChooseMostMatchingTree() {
    CTree* most_matching_tree;
    if (!children_population.empty()){
        most_matching_tree = children_population.at(0);
        for (int i=0; i<children_population.size();i++){
            if (most_matching_tree->getAccuracyRate()>children_population.at(i)->getAccuracyRate()){
                most_matching_tree = children_population.at(i);
            }
        }
    }
    return most_matching_tree;
}



