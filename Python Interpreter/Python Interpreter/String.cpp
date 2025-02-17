#include "String.h"

String::String(std::string& value)
{
	str = value;
}

bool String::isPrintable() const
{
	return true;
}

std::string String::toString() const
{
	// if there is a ' in the string return with "str"
	// if threre is no ' in the string return 'str'

	char c = '\'';
	bool b = false;
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == c)
		{
			b = true;
			break;
		}
	}

	// create a string of size str.size()
	std::string res = "";
	if (b)
	{
		res += "\"";
	}
	else
	{
		res += "'";
	}

	res += str;

	if (b)
	{
		res += "\"";
	}
	else
	{
		res += "'";
	}

	return res;
}