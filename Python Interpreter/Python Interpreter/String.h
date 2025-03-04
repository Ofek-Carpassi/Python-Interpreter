#ifndef STRING_H
#define STRING_H
#include "Type.h"

class String : public Type
{
public:
	String(std::string& value);

	virtual bool isPrintable() const;

	virtual std::string toString() const;
private:
	std::string str;
};

#endif