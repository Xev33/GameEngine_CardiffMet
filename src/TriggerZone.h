#ifndef GO_TEST_
#define GO_TEST_

#include <btBulletDynamicsCommon.h>
#include "AComponent.h"

namespace XDGameEngine
{
    class TriggerZone : public AComponent
    {
    protected:
        btDiscreteDynamicsWorld* m_dynamicsWorld;

        btRigidBody* m_rigidbody; /**< The rigidbody itself */
        btCollisionShape* m_colShape;  /**< Collision shape, describes the collision boundary */

        btScalar m_mass; /**< The body mass. 0 = static mesh */
    private:

    public:
        TriggerZone();
        ~TriggerZone();

        /**
        * Overrided method from AComponent. Connect the component to the dynamicWorld
        */
        virtual void SetUpComponent(GameObject& go) final;
    };
}

#endif