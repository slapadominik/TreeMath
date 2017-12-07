//
// Created by Domicik on 07.12.2017.
//

#include <sstream>
#include "StringValidator.h"

bool StringValidator::bIsNumber(const std::string &s) {
    std::istringstream iss(s);
    double d;
    return iss >> d >> std::ws && iss.eof();
}

bool StringValidator::bIsVariable(const std::string &s) {
    return (!s.empty() && !bIsNumber(s) && !bIsOneArgumentOperator(s) && !bIsTwoArgumentsOperator(s));
}

bool StringValidator::bIsTwoArgumentsOperator(const std::string &s) {
    return (s=="+" || s=="-" || s=="*" || s=="/");
}

bool StringValidator::bIsOneArgumentOperator(const std::string &s) {
    return (s=="sin" || s=="cos");
}




