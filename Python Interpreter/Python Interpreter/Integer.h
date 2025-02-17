#pragma once
#include "Type.h"
#include <iostream>

class Integer : public Type<int>
{
public:
	Integer(int value, bool isTemp);

	bool isPrintable() const;

	std::string toString() const;
};