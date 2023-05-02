#ifndef COLLISION_SHAPE_
#define COLLISION_SHAPE_

#include "AComponent.h"
#include "btBulletCollisionCommon.h"

namespace XDGameEngine
{
	/**
	* Base abstract class that any shape will inherit from
	*/
	class CollisionShape : public AComponent
	{
	protected:
		btCollisionShape* m_colShape;

	private:

	public:
		// Empty virtual destructor for an abstract class
		virtual ~CollisionShape() {}
	
		/**
		* Overrided method from AComponent. Create the right shape in the children classes
		*/
		virtual void SetUpComponent(GameObject& go) = 0;

		/**
		* ColShape setter
		*/
		void SetColShape(btCollisionShape* colShape) noexcept;

		/**
		* ColShape getter
		*/
		btCollisionShape* GetColShape() noexcept;

	};

	class BoxCollision : public CollisionShape
	{
		public:
			BoxCollision()
			{
				m_id = 'BXCS';
				m_colShape = nullptr;
			}
			~BoxCollision() {}

			virtual void SetUpComponent(GameObject& go) final;
	};

	class CapsuleCollision : public CollisionShape
	{
	public:
		CapsuleCollision()
		{
			m_id = 'CPCS';
			m_colShape = nullptr;
		}
		~CapsuleCollision() {}

		virtual void SetUpComponent(GameObject& go) final;
	};

	class CylinderCollision : public CollisionShape
	{
	public:
		CylinderCollision()
		{
			m_id = 'CLCS';
			m_colShape = nullptr;
		}
		~CylinderCollision() {}

		virtual void SetUpComponent(GameObject& go) final;
	};

	class SphereCollision : public CollisionShape
	{
	public:
		SphereCollision()
		{
			m_id = 'SPCS';
			m_colShape = nullptr;
		}
		~SphereCollision() {}

		virtual void SetUpComponent(GameObject& go) final;
	};
}

#endif