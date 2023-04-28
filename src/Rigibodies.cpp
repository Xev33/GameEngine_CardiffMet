#include "Rigibodies.h"

#include "CollisionShape.h"
#include "GameObject.h"

#include "Game.h"
#include "Scene.h"

namespace XDGameEngine
{
	Rigibody::Rigibody()
	{
		m_id = 'RGBD';

		m_dynamicsWorld = nullptr;
		m_rigidbody = nullptr;
		m_colShape = nullptr;

		m_mass = 1.0f;
		m_linearDamping = 0.6f;
		m_angularDamping = 0.1f;
	}

	Rigibody::~Rigibody()
	{
		m_dynamicsWorld->removeRigidBody(m_rigidbody);
		delete m_rigidbody->getMotionState();
		delete m_rigidbody;
	}

	void Rigibody::SetUpComponent(GameObject& go)
	{
		m_dynamicsWorld = Game::Instance()->getCurrentScene()->getDynamicWorld();
		m_colShape = go.GetComponent<CollisionShape>()->GetColShape();
		btTransform trans;

		if (m_colShape == nullptr)
			throw std::runtime_error("No CollisionShape* to associate with");
		trans.setIdentity();
		m_isDynamic = (m_mass != 0.0f);

		btVector3 localInertia(0, 0, 0);
		if (m_isDynamic)
		{
			m_colShape->calculateLocalInertia(m_mass, localInertia);
		}

		//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
		btDefaultMotionState* myMotionState = new btDefaultMotionState(trans);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(m_mass, myMotionState, m_colShape, localInertia);
		m_rigidbody = new btRigidBody(rbInfo);
		m_rigidbody->setDamping(m_linearDamping, m_angularDamping);
		m_rigidbody->setUserPointer((void*)this);
		m_dynamicsWorld->addRigidBody(m_rigidbody);
	}

	void Rigibody::UpdateComponent(GameObject& go)
	{
		btTransform trans;
		m_rigidbody->getMotionState()->getWorldTransform(trans);
		btQuaternion ortientation = trans.getRotation();

		// Here we update the gameObject's transform for the mesh to have the same coordinates
		go.GetTransform()->setPosition(trans.getOrigin());
		go.GetTransform()->setRotation(ortientation);
	}

	void Rigibody::SetActive(bool isActive)
	{
		if (isActive == true && m_isActive == false)
		{
			if (m_rigidbody != nullptr)
			{
				m_dynamicsWorld->addRigidBody(m_rigidbody);

				// It should have disable the component
				// without removing from the dynamic world but it doesn't work
				// and I don't have more time to spend on that

				//m_rigidbody->setActivationState(ACTIVE_TAG);
				//m_rigidbody->setLinearVelocity(m_prevVelocity);
				//m_rigidbody->getWorldTransform().setOrigin(m_prevPosition);
				//m_rigidbody->getWorldTransform().setRotation(m_prevRotation);
			}
		}
		else if (isActive == false && m_isActive == true)
		{
			if (m_rigidbody != nullptr)
			{
				m_dynamicsWorld->removeRigidBody(m_rigidbody);

				// It should have disable the component
				// without removing from the dynamic world but it doesn't work
				// and I don't have more time to spend on that

				//m_prevVelocity = m_rigidbody->getLinearVelocity();
				//m_prevPosition = m_rigidbody->getWorldTransform().getOrigin();
				//m_prevRotation = m_rigidbody->getWorldTransform().getRotation();
				//m_rigidbody->setActivationState(DISABLE_SIMULATION);
			}
		}
		m_isActive = isActive;
	}

	void Rigibody::SetMass(float mass) noexcept
	{
		m_mass = mass;

		if (m_mass == 0.0f)
			m_isDynamic = false;
		else
			m_isDynamic = true;
	}

	void Rigibody::SetLinearDamping(float linearDamping) noexcept
	{
		m_linearDamping = linearDamping;
	}

	void Rigibody::SetAngularDamping(float angularDamping) noexcept
	{
		m_angularDamping = angularDamping;
	}

	void Rigibody::SetRigidBody(btRigidBody* body) noexcept
	{
		m_rigidbody = body;
	}


	float Rigibody::GetMass() const noexcept
	{
		return m_mass;
	}

	float Rigibody::GetLinearDamping() const noexcept
	{
		return m_linearDamping;
	}

	float Rigibody::GetAngularDamping() const noexcept
	{
		return m_angularDamping;
	}

	bool Rigibody::IsDynamic() const noexcept
	{
		return m_isDynamic;
	}

	btRigidBody* Rigibody::GetRigidbody() noexcept
	{
		return m_rigidbody;
	}

}