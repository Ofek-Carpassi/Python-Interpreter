#include "Type.h"

Type::Type() : _isTemp(false) {}

void Type::setIsTemp(const bool isTemp)
{
	_isTemp = isTemp;
}

bool Type::getIsTemp() const
{
	return _isTemp;
}