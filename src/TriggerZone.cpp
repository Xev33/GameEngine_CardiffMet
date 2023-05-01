#include "TriggerZone.h"

#include "CollisionShape.h"
#include "GameObject.h"

#include "Game.h"
#include "Scene.h"

#include "OgreBullet.h"
namespace XDGameEngine
{
    TriggerZone::TriggerZone()
    {
        m_id = 'TGZN';

		m_dynamicsWorld = nullptr;
		m_rigidbody = nullptr;
		m_colShape = nullptr;
		m_mass = 0.0f;
	}

	TriggerZone::~TriggerZone()
	{
		m_dynamicsWorld->removeRigidBody(m_rigidbody);
		delete m_rigidbody->getMotionState();
		delete m_rigidbody;
	}

	void TriggerZone::SetUpComponent(GameObject& go)
	{
		m_dynamicsWorld = Game::Instance()->getCurrentScene()->getDynamicWorld();
		m_colShape = go.GetComponent<CollisionShape>()->GetColShape();
		btTransform trans;

	}
}