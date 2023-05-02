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
		m_ghostObj = nullptr;
		m_colShape = nullptr;
		m_mass = 0.0f;
	}

	TriggerZone::~TriggerZone()
	{
		m_dynamicsWorld->removeCollisionObject(m_ghostObj);

		delete m_ghostObj;
		m_ghostObj = nullptr;
	}

	void TriggerZone::SetUpComponent(GameObject& go)
	{
		m_dynamicsWorld = Game::Instance()->getCurrentScene()->getDynamicWorld();
		m_colShape = go.GetComponent<CollisionShape>()->GetColShape();
		btTransform trans(go.GetTransform()->getRotation(), go.GetTransform()->getPosition());

		btCollisionShape* shape = go.GetComponent<CollisionShape>()->GetColShape();
		if (shape == nullptr)
			return;
		m_ghostObj = new btGhostObject();
		m_ghostObj->setCollisionShape(shape);
		m_ghostObj->setCollisionFlags(m_ghostObj->getCollisionFlags() |
			btCollisionObject::CF_NO_CONTACT_RESPONSE);
		m_ghostObj->setWorldTransform(trans);
		m_dynamicsWorld->addCollisionObject(m_ghostObj);
	}

	uint32_t TriggerZone::OnTriggerEnter() const noexcept
	{
		if (m_ghostObj == nullptr)
			return '404';
		for (int i = 0, end = m_ghostObj->getNumOverlappingObjects(); i != end; ++i)
		{
			btCollisionObject* c = m_ghostObj->getOverlappingObject(i);
			MyContactResultCallback results;
			m_dynamicsWorld->contactPairTest(m_ghostObj, c, results);
			if (results.hitObject)
			{
				uint32_t* tag = static_cast<uint32_t*>(c->getUserPointer());
				std::cout << "Collision with tag number: " << *tag << std::endl;
				return *tag;
			}
		}
		return '404';
	}

}