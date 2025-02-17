#include "Boolean.h"

Boolean::Boolean(bool b) : val(b) {}

bool Boolean::isPrintable() const
{
	return true;
}

std::string Boolean::toString() const
{
	return val ? "True" : "False";
}