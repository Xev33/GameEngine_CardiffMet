#include "Input.h"
#include <iostream>

namespace XDGameEngine
{
	Input::Input()
	{
		m_id = 'INPT';
		std::cout << " INPUT CREATED\n";
	}

	Input::~Input()
	{
		std::cout << " INPUT DESTRUCTED\n";
		printIntest();
	}

	void Input::printTruc()
	{
		std::cout << "INPUT PRINT UN TRUC\n";
	}
}