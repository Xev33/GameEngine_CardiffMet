#include "Rigibodies.h"
#include <iostream>

namespace XDGameEngine
{
	Rigibody::Rigibody()
	{
		m_id = 'RGBD';
		std::cout << " RIGIBODY CREATED\n";

		m_mass = 1.0f;
		m_rigidbody = nullptr;
		m_dynamicsWorld = nullptr;
		m_colShape = nullptr;
	}

	Rigibody::~Rigibody()
	{
		std::cout << " RIGIBODY DESTRUCTED\n";
	}

	void Rigibody::SetMass(float mass) noexcept
	{
		m_mass = mass;
	}

	float Rigibody::GetMass() const noexcept
	{
		return m_mass;
	}
}