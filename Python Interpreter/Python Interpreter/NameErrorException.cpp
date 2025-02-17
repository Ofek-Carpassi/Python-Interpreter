#include "NameErrorException.h"

NameErrorException::NameErrorException(const std::string& name) : name(name)
{}

const char* NameErrorException::what() const throw()
{
    std::string tmp = "NameError: name " + name + " is not defined";
    return tmp.c_str();
}