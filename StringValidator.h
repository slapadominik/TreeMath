#include <string>

#ifndef TREEMATH_STRINGVALIDATOR_H
#define TREEMATH_STRINGVALIDATOR_H


class StringValidator {
public:
    static bool bIsNumber(const std::string &s);
    static bool bIsVariable(const std::string &s);
    static bool bIsTwoArgumentsOperator(const std::string &s);
    static bool bIsOneArgumentOperator(const std::string &s);
};


#endif //TREEMATH_STRINGVALIDATOR_H
