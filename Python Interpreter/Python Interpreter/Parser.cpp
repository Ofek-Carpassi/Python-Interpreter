#include "Parser.h"
#include <iostream>
#include "Helper.h"
#include "Type.h"
#include "InterpreterException.h"
#include "IndentationException.h"
#include "SyntaxException.h"
#include "Integer.h"
#include "Boolean.h"
#include "String.h"
#include "NameErrorException.h"

std::unordered_map<std::string, Type*> Parser::variables;

Type* Parser::parseString(const std::string& str)
{
    if (str.empty()) return nullptr;

    if (str[0] == ' ' || str[0] == '\t')
        throw IndentationException();

    // Remove white spaces
    std::string trimmed = str;
    Helper::trim(trimmed);

    // Check if the string is a variable
    Type* typeOfVar = getVariableValue(trimmed);
    if (typeOfVar != nullptr)
        return typeOfVar;

    // Check if the string is an assignment
    if (makeAssignment(trimmed))
        return nullptr;

    Type* t = getTypeStatic(trimmed);
    if (t == nullptr)
        throw SyntaxException();    

    t->setIsTemp(true); // Mark as temporary so it gets cleaned up
    return t;
}

Type* Parser::getTypeStatic(std::string& str)
{
	// Start by removing white spaces in the start
	Helper::trim(str);

	Type* t = nullptr;

	if (Helper::isInteger(str))
	{
		Helper::removeLeadingZeros(str);
		t = new Integer(std::stoi(str));
	}
	else if (Helper::isBoolean(str))
	{
		bool b = str == "True" ? true : false;
		t = new Boolean(b);
	}
	else if (Helper::isString(str))
		t = new String(str);
	else
		return nullptr;

	return t;
}

bool Parser::isLegalVarName(const std::string& str)
{
    if (str.empty() || Helper::isDigit(str[0]))
        return false;
    
    for (char c : str)
        if (!(Helper::isLetter(c) || Helper::isDigit(c) || Helper::isUnderscore(c)))
            return false;
    
    return true;
}

bool Parser::makeAssignment(const std::string& str)
{
    std::size_t pos = str.find("=");
    if (pos == std::string::npos)
        return false;

    std::string varName = str.substr(0, pos);
    std::string varValue = str.substr(pos + 1);

    Helper::trim(varName);
    Helper::trim(varValue);

    if (!isLegalVarName(varName))
        throw NameErrorException(varName);

    // First check if varValue is a variable name
    Type* sourceVar = getVariableValue(varValue);
    Type* t = nullptr;
    
    if (sourceVar != nullptr) {
        if (auto intVal = dynamic_cast<Integer*>(sourceVar))
            t = new Integer(std::stoi(intVal->toString()));
        else if (auto boolVal = dynamic_cast<Boolean*>(sourceVar))
            t = new Boolean(boolVal->toString() == "True");
        else if (auto strVal = dynamic_cast<String*>(sourceVar)) {
            std::string value = strVal->toString();
            value = value.substr(1, value.length() - 2);
            t = new String(value);
        }
    } else {
        t = getTypeStatic(varValue);
        if (t == nullptr)
            throw NameErrorException(varValue);
    }

    // Clean up previous value if it exists
    auto it = variables.find(varName);
    if (it != variables.end()) {
        delete it->second;
        variables.erase(it);
    }

    variables.emplace(varName, t);
    return true;
}

Type* Parser::getVariableValue(std::string& str)
{
	// Remove white spaces
	Helper::trim(str);
	if (variables.find(str) == variables.end())
		return nullptr;
	return variables[str];
}

void Parser::clearVariables()
{
	for (auto it = variables.begin(); it != variables.end(); it++)
		delete it->second;

	variables.clear();
}