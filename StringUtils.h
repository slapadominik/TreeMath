#include <string>

#ifndef TREEMATH_STRINGVALIDATOR_H
#define TREEMATH_STRINGVALIDATOR_H


class StringUtils {
public:
    static bool bIsNumber(const std::string &s);
    static bool bIsVariable(const std::string &s);
    static bool bIsTwoArgumentsOperator(const std::string &s);
    static bool bIsOneArgumentOperator(const std::string &s);
    static std::string intToString(int value);
    static std::string charToString(const char letter);
};


#endif //TREEMATH_STRINGVALIDATOR_H
