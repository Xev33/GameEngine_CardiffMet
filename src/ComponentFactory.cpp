#include "ComponentFactory.h"
#include "MeshRenderer.h"
#include "Rigibodies.h"
#include "Transform.h"
#include "CollisionShape.h"
#include <memory>
#include "GameObject.h"
#include "TriggerZone.h"

namespace XDGameEngine
{
	ComponentFactory::ComponentFactory()
	{
	}

	ComponentFactory::~ComponentFactory()
	{
	}

	std::unique_ptr<XDGameEngine::AComponent> ComponentFactory::CreateComponent(uint32_t componentType, GameObject& go,
		const btVector3 pos, const btQuaternion rot, const btVector3 scale)
	{
		switch (componentType) {
		case 'TRFM':
			return std::make_unique<Transform>(pos, rot, scale);
		case 'RGBD':
			return std::make_unique<RigidBody>();
		case 'MSRD':
			return std::make_unique<MeshRenderer>();
		case 'BXCS':
			return std::make_unique<BoxCollision>();
		case 'CPCS':
			return std::make_unique<CapsuleCollision>();
		case 'CLCS':
			return std::make_unique<CylinderCollision>();
		case 'SPCS':
			return std::make_unique<SphereCollision>();
		case 'TGZN':
			return std::make_unique<TriggerZone>();
		default:
			throw std::runtime_error("Invalid game type.");
		}
	}
}
