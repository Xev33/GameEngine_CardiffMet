#include "ComponentFactory.h"
#include "MeshRenderer.h"
#include "Input.h"
#include <memory>

namespace XDGameEngine
{
	ComponentFactory::ComponentFactory()
	{

	}

	ComponentFactory::~ComponentFactory()
	{

	}

	std::unique_ptr<XDGameEngine::AComponent> ComponentFactory::CreateComponent(uint32_t componentType)
	{
		switch (componentType) {
		case 'MSRD':
			return std::make_unique<XDGameEngine::Input>();
		case'INPT':
			return std::make_unique<XDGameEngine::MeshRenderer>();
		default:
			throw std::runtime_error("Invalid game type.");
		}
	}
}
