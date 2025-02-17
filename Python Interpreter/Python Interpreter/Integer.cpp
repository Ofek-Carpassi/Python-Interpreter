#include "Integer.h"
#include <string>

Integer::Integer(int v) : val(v) {}

bool Integer::isPrintable() const
{
	return true;
}

std::string Integer::toString() const
{
	return std::to_string(val);
}