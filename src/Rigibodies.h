#ifndef RIGIBODY_
#define RIGIBODY_

#include "AComponent.h"
#include "btBulletDynamicsCommon.h"

namespace XDGameEngine
{
    class Rigibody : public AComponent
    {
    protected:
    private:
        btRigidBody* m_rigidbody;
        btDiscreteDynamicsWorld* m_dynamicsWorld;

        btCollisionShape* m_colShape;  /**< Collision shape, describes the collision boundary */

        btScalar m_mass;
        btScalar linearDamping; /**< Damping force on the linear motion of the body, kind of air/friction */
        btScalar angularDamping; /**< Damping force on the angular motion of the body, kind of air/friction */

    public:
        Rigibody();
        ~Rigibody();

        void SetMass(float mass) noexcept;
        float GetMass() const noexcept;
    };
}

#endif