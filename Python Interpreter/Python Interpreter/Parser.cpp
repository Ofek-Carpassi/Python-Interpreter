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

Type* Parser::parseString(std::string str)
{
	if (str.length() <= 0) return nullptr;

	if (str[0] == ' ' || str[0] == '\t')
		throw IndentationException();

	// Remove white spaces
	Helper::trim(str);

	Type* t = getType(str);

	if (t == nullptr)
		throw SyntaxException();	

	return t;
}

Type* Parser::getType(std::string& str)
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