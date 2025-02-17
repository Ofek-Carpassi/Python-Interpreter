#include "String.h"

String::String(std::string str, bool isTemp) : Sequence(str, isTemp)
{
	this->value = str;
}

bool String::isPrintable() const
{
	return true;
}

std::string String::toString() const
{
	return this->value;
}