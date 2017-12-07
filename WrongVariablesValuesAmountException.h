//
// Created by Domicik on 17.11.2017.
//

#ifndef TREEMATH_WRONGVARIABLESVALUESAMOUNTEXCEPTION_H
#define TREEMATH_WRONGVARIABLESVALUESAMOUNTEXCEPTION_H

#include <exception>
#include <string>

class WrongVariablesValuesAmountException : public std::exception {

public:
    WrongVariablesValuesAmountException(std::string msg);
    std::string getMessage();
private:
    std::string msg;

};


#endif //TREEMATH_WRONGVARIABLESVALUESAMOUNTEXCEPTION_H
