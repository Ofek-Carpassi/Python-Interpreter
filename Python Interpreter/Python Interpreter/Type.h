#pragma once
#include <iostream>

template <typename T>
class Type
{
public:
	Type(T value, bool isTemp);

	bool getIsTemp() const;
	T getValue() const;

	void setIsTemp(bool isTemp);
	void setValue(T value);

	bool isPrintable() const;

	std::string toString() const;

private:
	T _value;
	bool _isTemp
};