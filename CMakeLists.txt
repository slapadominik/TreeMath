cmake_minimum_required(VERSION 3.8)
project(TreeMath)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp CNode.cpp CNode.h CTree.cpp CTree.h WrongVariablesValuesAmountException.cpp WrongVariablesValuesAmountException.h EmptyTreeException.cpp EmptyTreeException.h Interface.cpp Interface.h StringUtils.cpp StringUtils.h RandomTreeGenerator.cpp RandomTreeGenerator.h GeneticProgramming.cpp GeneticProgramming.h FileReader.cpp FileReader.h)
add_executable(TreeMath ${SOURCE_FILES})