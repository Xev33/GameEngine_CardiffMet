#include "Rigibodies.h"

#include "CollisionShape.h"
#include "GameObject.h"

#include "Game.h"
#include "Scene.h"

#include "OgreBullet.h"
namespace XDGameEngine
{
	RigidBody::RigidBody()
	{
		m_id = 'RGBD';

		m_dynamicsWorld = nullptr;
		m_rigidbody = nullptr;
		m_colShape = nullptr;

		m_mass = 1.0f;
		m_linearDamping = 0.6f;
		m_angularDamping = 0.1f;
	}

	RigidBody::~RigidBody()
	{
		m_dynamicsWorld->removeRigidBody(m_rigidbody);
		delete m_rigidbody->getMotionState();
		delete m_rigidbody;
	}

	void RigidBody::SetUpComponent(GameObject& go)
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

		// We replace the gameobject
		Vector3 axis(go.GetTransform()->getPosition().getX(),
			go.GetTransform()->getPosition().getY(),
			go.GetTransform()->getPosition().getZ());
		Radian rads(Ogre::Degree(go.GetTransform()->getRotation().getY()));
		Ogre::Quaternion quat(rads, axis);
		btQuaternion rotation = Ogre::Bullet::convert(quat);

		btVector3 pos(go.GetTransform()->getPosition().getX(),
			go.GetTransform()->getPosition().getY(),
			go.GetTransform()->getPosition().getZ());

		trans.setOrigin(pos);
		trans.setRotation(rotation);

		//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
		btDefaultMotionState* myMotionState = new btDefaultMotionState(trans);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(m_mass, myMotionState, m_colShape, localInertia);
		m_rigidbody = new btRigidBody(rbInfo);
		m_rigidbody->setDamping(m_linearDamping, m_angularDamping);
		m_rigidbody->setUserPointer((void*)this);
		m_dynamicsWorld->addRigidBody(m_rigidbody);
	}

	void RigidBody::UpdateComponent(GameObject& go)
	{
		btTransform trans;
		m_rigidbody->getMotionState()->getWorldTransform(trans);
		btQuaternion ortientation = trans.getRotation();

		// Here we update the gameObject's transform for the mesh to have the same coordinates
		go.GetTransform()->setPosition(trans.getOrigin());
		go.GetTransform()->setRotation(ortientation);
	}

	void RigidBody::SetActive(bool isActive)
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

	void RigidBody::SetMass(float mass) noexcept
	{
		m_mass = mass;

		if (m_mass == 0.0f)
			m_isDynamic = false;
		else
			m_isDynamic = true;
	}

	void RigidBody::SetLinearDamping(float linearDamping) noexcept
	{
		m_linearDamping = linearDamping;
	}

	void RigidBody::SetAngularDamping(float angularDamping) noexcept
	{
		m_angularDamping = angularDamping;
	}

	void RigidBody::SetRigidBody(btRigidBody* body) noexcept
	{
		m_rigidbody = body;
	}


	float RigidBody::GetMass() const noexcept
	{
		return m_mass;
	}

	float RigidBody::GetLinearDamping() const noexcept
	{
		return m_linearDamping;
	}

	float RigidBody::GetAngularDamping() const noexcept
	{
		return m_angularDamping;
	}

	bool RigidBody::IsDynamic() const noexcept
	{
		return m_isDynamic;
	}

	btRigidBody* RigidBody::GetRigidbody() noexcept
	{
		return m_rigidbody;
	}

	/* Based on the code from the earlier ray casting example */
	bool RigidBody::IsGrounded() const noexcept
	{
		btTransform trans;
		m_rigidbody->getMotionState()->getWorldTransform(trans);

		// Cast a vector down - 100 from the center down 50 units below the object.
		// took into account the bottom of the object.
		// The coordinates are in world space.
		btVector3 start(trans.getOrigin());
		btVector3 end(start.x(), start.y() - 100, start.z());

		btCollisionWorld::ClosestRayResultCallback closesRayCallback(start, end);
		m_dynamicsWorld->rayTest(start, end, closesRayCallback);

		if (closesRayCallback.hasHit())
		{
			// Reset linear damping after fall. 
			m_rigidbody->setDamping(m_linearDamping, m_angularDamping);

			return true;
		}
		else
		{
			return false;
		}
	}

}