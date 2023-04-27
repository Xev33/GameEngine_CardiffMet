#include "CollisionShape.h"
#include "OgreBullet.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "AComponent.h"

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
	void BoxCollision::SetUpComponent(GameObject& go) noexcept
	{
		Ogre::Entity* shape = go.GetComponent<MeshRenderer>()->GetMesh();

		if (shape != nullptr)
			m_colShape = Ogre::Bullet::createBoxCollider(shape);
		else
			throw std::runtime_error("No Ogre::Entity* to associate with");
	}

	// CAPSULE COLLISION ---------------------------------------------
	void CapsuleCollision::SetUpComponent(GameObject& go) noexcept
	{
		Ogre::Entity* shape = go.GetComponent<MeshRenderer>()->GetMesh();

		if (shape != nullptr)
			m_colShape = Ogre::Bullet::createCapsuleCollider(shape);
		else
			throw std::runtime_error("No Ogre::Entity* to associate with");
	}

	// CYLINDER COLLISION --------------------------------------------
	void CylinderCollision::SetUpComponent(GameObject& go) noexcept
	{
		Ogre::Entity* shape = go.GetComponent<MeshRenderer>()->GetMesh();

		if (shape != nullptr)
			m_colShape = Ogre::Bullet::createCylinderCollider(shape);
		else
			throw std::runtime_error("No Ogre::Entity* to associate with");
	}

	// SPHERE COLLISION ---------------------------------------------
	void SphereCollision::SetUpComponent(GameObject& go) noexcept
	{
		Ogre::Entity* shape = go.GetComponent<MeshRenderer>()->GetMesh();

		if (shape != nullptr)
			m_colShape = Ogre::Bullet::createSphereCollider(shape);
		else
			throw std::runtime_error("No Ogre::Entity* to associate with");
	}

}