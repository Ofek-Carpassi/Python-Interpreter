#include "Integer.h"

Integer::Integer(int value, bool isTemp) : Type(value, isTemp)
{}

bool Integer::isPrintable() const
{
	return true;
}

std::string Integer::toString() const
{
	return "";
}