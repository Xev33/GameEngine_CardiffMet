#include "Transform.h"

namespace XDGameEngine
{
	Transform::Transform()
	{
		m_id = 'TRFM';
		std::cout << " TRANSFORM CREATED\n";
	}

	Transform::~Transform()
	{
		std::cout << " TRANSFORM DESTRUCTED\n";
	}

	void Transform::printUnAutreTruc()
	{
		std::cout << "TRANSFORM PRINT UN TRUC\n";
	}

}