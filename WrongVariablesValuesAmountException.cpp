//
// Created by Domicik on 17.11.2017.
//

#include "WrongVariablesValuesAmountException.h"

WrongVariablesValuesAmountException::WrongVariablesValuesAmountException(std::string msg) {
    this->msg=msg;
}

std::string WrongVariablesValuesAmountException::getMessage() {
    return msg;
}

