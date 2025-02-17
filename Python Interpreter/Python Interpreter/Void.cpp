#include "Void.h"

Void::Void() : Type<void>(nullptr, false)
{
}

bool Void::isPrintable() const
{
	return false;
}

std::string Void::toString() const
{
	return "void";
}