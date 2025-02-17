#ifndef TYPE_H
#define TYPE_H
#include "Type.h"

class Boolean : public Type
{
public:
	Boolean(bool b);

	virtual bool isPrintable() const;
	virtual std::string toString() const;

private:
	bool val;
};

#endif