//
// Created by Domicik on 07.12.2017.
//

#include <sstream>
#include "StringUtils.h"

bool StringUtils::bIsNumber(const std::string &s) {
    std::istringstream iss(s);
    double d;
    return iss >> d >> std::ws && iss.eof();
}

bool StringUtils::bIsVariable(const std::string &s) {
    return (!s.empty() && !bIsNumber(s) && !bIsOneArgumentOperator(s) && !bIsTwoArgumentsOperator(s));
}

bool StringUtils::bIsTwoArgumentsOperator(const std::string &s) {
    return (s=="+" || s=="-" || s=="*" || s=="/");
}

bool StringUtils::bIsOneArgumentOperator(const std::string &s) {
    return (s=="sin" || s=="cos");
}

std::string StringUtils::intToString(int number) {
    std::stringstream ss;
    ss<<number;
    return ss.str();

}

std::string StringUtils::charToString(const char letter) {
    std::string str(1, letter);
    return str;
}




