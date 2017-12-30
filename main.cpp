#include <iostream>
#include <cstdlib>
#include <time.h>
#include "Interface.h"
#include "StringUtils.h"
#include "RandomTreeGenerator.h"
#include "GeneticProgramming.h"
#include "FileReader.h"


int main() {
    srand(time(NULL));

    GeneticProgramming geneticProgramming;
    geneticProgramming.initializeDataFromFile("data_function.txt");
    geneticProgramming.initializePopulation(50);
    geneticProgramming.evaluate();
    for (int i=0;i<3;i++){
        geneticProgramming.vRunIteration();
        geneticProgramming.vAfterIteration();
    }
    geneticProgramming.vRunIteration();
    geneticProgramming.printBeginningPopulation();

    std::cout<<"---------"<<std::endl;
    geneticProgramming.printParentsPopulation();
    std::cout<<"---------"<<std::endl;
    geneticProgramming.printChildrenPopulation();
    std::cout<<"---------"<<std::endl;
    std::cout<<"---------"<<std::endl;
    std::cout<<"---------"<<std::endl;

    return 0;
}



