#include "Parser.h"
#include <iostream>
#include "Helper.h"
#include "Type.h"
#include "InterpreterException.h"
#include "IndentationException.h"

Type* Parser::parseString(std::string str)
{
	if (str.length() <= 0) return nullptr;

	if (str[0] == ' ' || str[0] == '\t')
		throw IndentationException();


}

Type* getType(std::string& str)
{

}