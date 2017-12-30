//
// Created by Ululula on 27.12.2017.
//

#ifndef TREEMATH_GENETICPROGRAMMING_H
#define TREEMATH_GENETICPROGRAMMING_H


#include "CTree.h"

class GeneticProgramming {
public:
    GeneticProgramming();
    ~GeneticProgramming();
    bool initializeDataFromFile(std::string fileName);
    void initializePopulation(int iTreesAmount);
    void evaluate();
    void evaluateChildrenPopulation();
    void printBeginningPopulation();
    void printParentsPopulation();
    void selection();
    void printVectorValues();
    CTree* tournament(CTree *tree1, CTree *tree2);
    void crossbreedPairOfTrees(CTree *tree1, CTree *tree2);
    void crossbreedParentsPopulation();
    void printChildrenPopulation();
    void mutation();
    void vRunIteration();
    void vAfterIteration();

private:
    std::vector<double> x_y_xy_values;
    std::vector<CTree*> beginning_population;
    std::vector<CTree*> parents_population;
    std::vector<CTree*> children_population;
    bool b_is_data_initialized;

    void v_clear_beginning_population();
    void v_clear_children_popualtion();
    double calculate_accuracy_rate_for_tree(CTree &tree);


};


#endif //TREEMATH_GENETICPROGRAMMING_H
