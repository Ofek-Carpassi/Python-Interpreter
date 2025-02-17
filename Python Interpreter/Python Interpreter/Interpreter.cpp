#include "Type.h"
#include "InterpreterException.h"
#include "Parser.h"
#include <iostream>

#define WELCOME "Welcome to Magshimim Python Interperter version 1.0 by "
#define YOUR_NAME "Ofek Carpassi"

int main(int argc,char **argv)
{
	std::cout << WELCOME << YOUR_NAME << std::endl;

	std::string input_string;

	// get new command from user
	std::cout << ">>> ";
	std::getline(std::cin, input_string);
	
	while (input_string != "quit()")
	{
		// parsing command
		try {
			Type* result = Parser::parseString(input_string);
			if (result->isPrintable()) {
				std::cout << result->toString() << std::endl;
			}
			if (result->getIsTemp())
			{
				delete result;
			}
		}
		catch (InterpreterException& e) {
			std::cout << e.what() << std::endl;
		}


		// get new command from user
		std::cout << ">>> ";
		std::getline(std::cin, input_string);
	}

	return 0;
}
