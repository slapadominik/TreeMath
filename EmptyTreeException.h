//
// Created by Domicik on 17.11.2017.
//

#ifndef TREEMATH_EMPTYTREEEXCEPTION_H
#define TREEMATH_EMPTYTREEEXCEPTION_H
#include <exception>
#include <string>

class EmptyTreeException : public std::exception{
public:
    EmptyTreeException(std::string number);
    std::string getMessage();
private:
    std::string msg;
};


#endif //TREEMATH_EMPTYTREEEXCEPTION_H
