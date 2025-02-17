#pragma once
#include "InterpreterException.h"
#include <iostream>

class NameErrorException : public InterpreterException
{
public:
    NameErrorException(const std::string& name);
    virtual const char* what() const throw();

private:
    std::string name;
};