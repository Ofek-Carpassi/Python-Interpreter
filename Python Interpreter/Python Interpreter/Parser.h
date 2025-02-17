#pragma once
#include "InterpreterException.h"
#include "Type.h"
#include "Helper.h"
#include <string>
#include <unordered_map>
#include <iostream>
#include <sstream>
#include "Integer.h"
#include "String.h"
#include "Boolean.h"
#include "Void.h"


class Parser
{
public:
    static Type* parseString(std::string str);
    static Type* getType(std::string &str);

private:

};
