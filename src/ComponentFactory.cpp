#include "ComponentFactory.h"
#include "MeshRenderer.h"
#include "Rigibodies.h"
#include "Transform.h"
#include <memory>
#include "GameObject.h"

namespace XDGameEngine
{
	ComponentFactory::ComponentFactory()
	{

	}

	ComponentFactory::~ComponentFactory()
	{

	}

	std::unique_ptr<XDGameEngine::AComponent> ComponentFactory::CreateComponent(uint32_t componentType, GameObject& go)
	{
		switch (componentType) {
		case 'TRFM':
			return std::make_unique<XDGameEngine::Transform>();
		case 'RGBD':
			return std::make_unique<XDGameEngine::Rigibody>();
		case 'MSRD':
			return std::make_unique<XDGameEngine::MeshRenderer>();
		default:
			throw std::runtime_error("Invalid game type.");
		}
	}
}