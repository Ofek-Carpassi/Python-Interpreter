#include "Type.h"

template <typename T>
Type<T>::Type(T value, bool isTemp) : _value(Value), _isTemp(isTemp)
{}

template <typename T>
bool Type<T>::getIsTemp() const
{
	return _isTemp;
}

template <typename T>
T Type<T>::getValue() const
{
	return _value;
}

template <typename T>
void Type<T>::setIsTemp(bool isTemp)
{
	_isTemp = isTemp;
}

template <typename T>
void Type<T>::setValue(T value)
{
	_value = value;
}

template <typename T>
bool Type<T>::isPrintable() const
{
	return true;
}

template <typename T>
std::string Type<T>::toString() const
{
	return "";
}