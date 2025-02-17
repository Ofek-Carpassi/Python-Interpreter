#pragma once
#include "Sequence.h"

class String : public Sequence<std::string>
{
public:
	String(std::string value, bool isTemp);

	bool isPrintable() const;

	std::string toString() const;

private:
	std::string value;
};