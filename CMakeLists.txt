cmake_minimum_required(VERSION 3.8)
project(TreeMath)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp CNode.cpp CNode.h CTree.cpp CTree.h WrongVariablesValuesAmountException.cpp WrongVariablesValuesAmountException.h EmptyTreeException.cpp EmptyTreeException.h Interface.cpp Interface.h StringValidator.cpp StringValidator.h SmiesznaKlasa.cpp SmiesznaKlasa.h)
add_executable(TreeMath ${SOURCE_FILES})