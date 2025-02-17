#include "Boolean.h"

Boolean::Boolean(bool value, bool isTemp) : Type(value, isTemp)
{}

bool Boolean::isPrintable() const
{
	return true;
}

std::string Boolean::toString() const
{
	return "";
}