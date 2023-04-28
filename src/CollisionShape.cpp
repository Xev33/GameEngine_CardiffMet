#include "CollisionShape.h"
#include "OgreBullet.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Game.h"
#include "Scene.h"

namespace XDGameEngine
{
	// COLLISION SHAPE -----------------------------------------------
	void CollisionShape::SetColShape(btCollisionShape* colShape) noexcept
	{
		m_colShape = colShape;
	}

	btCollisionShape* CollisionShape::GetColShape() noexcept
	{
		return m_colShape;
	}

	// ----------------------------------------------------------------
	// ----------------------------------------------------------------
	// ----------------------------------------------------------------
	// ----------------------------------------------------------------
	// ----------------------------------------------------------------
	// ----------------------------------------------------------------
	// ----------------------------------------------------------------

	// BOX COLLISION -------------------------------------------------
	void BoxCollision::SetUpComponent(GameObject& go)
	{
		Ogre::Entity* shape = go.GetComponent<MeshRenderer>()->GetMesh();

		if (shape == nullptr)
			throw std::runtime_error("No Ogre::Entity* to associate with");
		m_colShape = Ogre::Bullet::createBoxCollider(shape);
		Game::Instance()->getCurrentScene()->getCollisionShapes()->push_back(m_colShape);
	}

	// CAPSULE COLLISION ---------------------------------------------
	void CapsuleCollision::SetUpComponent(GameObject& go)
	{
		Ogre::Entity* shape = go.GetComponent<MeshRenderer>()->GetMesh();

		if (shape == nullptr)
			throw std::runtime_error("No Ogre::Entity* to associate with");
		m_colShape = Ogre::Bullet::createCapsuleCollider(shape);
		Game::Instance()->getCurrentScene()->getCollisionShapes()->push_back(m_colShape);
	}

	// CYLINDER COLLISION --------------------------------------------
	void CylinderCollision::SetUpComponent(GameObject& go)
	{
		Ogre::Entity* shape = go.GetComponent<MeshRenderer>()->GetMesh();

		if (shape == nullptr)
			throw std::runtime_error("No Ogre::Entity* to associate with");
		m_colShape = Ogre::Bullet::createCylinderCollider(shape);
		Game::Instance()->getCurrentScene()->getCollisionShapes()->push_back(m_colShape);
	}

	// SPHERE COLLISION ---------------------------------------------
	void SphereCollision::SetUpComponent(GameObject& go)
	{
		Ogre::Entity* shape = go.GetComponent<MeshRenderer>()->GetMesh();

		if (shape == nullptr)
			throw std::runtime_error("No Ogre::Entity* to associate with");
		m_colShape = Ogre::Bullet::createSphereCollider(shape);
		Game::Instance()->getCurrentScene()->getCollisionShapes()->push_back(m_colShape);
	}

}