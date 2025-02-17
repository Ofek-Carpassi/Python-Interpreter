#pragma once
#include "Type.h"

class Boolean : public Type<bool>
{
public:
	Boolean(bool value, bool isTemp);

	bool isPrintable() const;

	std::string toString() const;
}