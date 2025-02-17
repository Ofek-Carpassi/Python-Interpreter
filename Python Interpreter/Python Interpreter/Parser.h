#pragma once
#include "InterpreterException.h"
#include "Type.h"
#include "Helper.h"
#include <string>
#include <unordered_map>
#include <iostream>
#include <sstream>


class Parser
{
public:
    static Type* parseString(std::string str);
    //Type* getType(std::string& str);
    static Type* getTypeStatic(std::string str);
    static void clearVariables();

private:
    static bool isLegalVarName(std::string str);
    static bool makeAssignment(std::string str);
    static Type* getVariableValue(std::string str);

    static std::unordered_map<std::string, Type*> variables;

};
