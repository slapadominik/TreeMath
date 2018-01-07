//
// Created by Domicik on 17.11.2017.
//

#include "EmptyTreeException.h"

EmptyTreeException::EmptyTreeException(std::string msg) {
    this->msg=msg;
}

std::string EmptyTreeException::getMessage() {
    return msg;
}
