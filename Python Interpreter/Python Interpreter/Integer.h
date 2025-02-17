#ifndef INTEGER_H
#define INTEGER_H
#include "Type.h"
#include <iostream>

class Integer : public Type
{
public:
	Integer(int v);

	virtual bool isPrintable() const;

	virtual std::string toString() const;

private:
	int val;
};

#endif