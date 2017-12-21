#include <iostream>
#include <cstdlib>
#include <time.h>
#include "Interface.h"
#include "StringUtils.h"
#include "RandomNodeGenerator.h"


int main() {
    CNode* node = RandomNodeGenerator::generateRandomTree();
    std::cout<<node->toString()<<std::endl;
    delete node;
    return 0;
}



