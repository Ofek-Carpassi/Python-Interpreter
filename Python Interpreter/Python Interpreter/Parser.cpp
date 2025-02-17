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

Type* Parser::parseString(std::string str)
{
	if (str.length() <= 0) return nullptr;

	if (str[0] == ' ' || str[0] == '\t')
		throw IndentationException();

	// Remove white spaces
	Helper::trim(str);

	// Check if the string is an assignment
	if (makeAssignment(str))
		return nullptr;

	Type* t = getTypeStatic(str);

	if (t == nullptr)
		throw SyntaxException();	

	return t;
}

Type* Parser::getTypeStatic(std::string str)
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
	{
		int length = str.length();
		t = new String(str);
	}
	else
		return nullptr;

	return t;
}

bool Parser::isLegalVarName(std::string str)
{
	bool isLegal = true;

	if (str.length() <= 0) isLegal = false;

	if (str[0] >= '0' && str[0] <= '9')
		isLegal = false;

	for (int i = 0; i < str.length(); i++)
		if ((str[i] < 'a' || str[i] > 'z') && (str[i] < 'A' || str[i] > 'Z') && (str[i] < '0' || str[i] > '9'))
			isLegal = false;

	return isLegal;
}

bool Parser::makeAssignment(std::string str)
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

	Type* t = getTypeStatic(varValue);

	if (t == nullptr)
		throw SyntaxException();

	if (variables.find(varName) != variables.end())
	{
		delete variables[varName];
		variables.erase(varName);
	}

	variables[varName] = t;

	return true;

}

Type* Parser::getVariableValue(std::string str)
{
	// Remove white spaces
	Helper::trim(str);

	if (variables.find(str) == variables.end())
		return NULL;

	return variables[str];
}

void Parser::clearVariables()
{
	for (auto it = variables.begin(); it != variables.end(); it++)
		delete it->second;

	variables.clear();
}