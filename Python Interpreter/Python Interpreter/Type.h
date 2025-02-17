#pragma once
#include <iostream>
#include <string>
#include "Type.h"

class Type
{
public:
	Type();

	void setIsTemp(const bool isTemp);
	bool getIsTemp() const;

	virtual bool isPrintable() const = 0;
	virtual std::string toString() const = 0;

protected:
	bool _isTemp;
};