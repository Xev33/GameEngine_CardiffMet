#include "Rigibodies.h"
#include <iostream>

namespace XDGameEngine
{
	Rigibody::Rigibody()
	{
		std::cout << " RIGIBODY CREATED\n";
	}

	Rigibody::~Rigibody()
	{
		std::cout << " RIGIBODY DESTRUCTED\n";
		printIntest();
	}

	void Rigibody::printTruc()
	{
		std::cout << "RIGIBODY PRINT UN TRUC\n";
	}
}