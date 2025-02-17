#pragma once
#include "Type.h"

// Sequence - abstract class that represents a sequence of another type

template <typename T>
class Sequence : public Type<T>
{
public:
	Sequence(T value, bool isTemp);

private:
};