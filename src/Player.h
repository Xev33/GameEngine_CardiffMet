#ifndef Player_
#define Player_

#include "GameObject.h"
#include "ComponentFactory.h"
#include "AComponent.h"
#include "Rigibodies.h"

namespace XDGameEngine
{
    class Player : public XDGameEngine::GameObject
    {
    protected:

    private:

        float m_forwardForce;
        float m_turningForce;
        float m_jumpForce;

        float m_linearDamping;
        float m_angularDamping;

        btRigidBody* m_rgbd;

    public:
        Player();
        ~Player();

        virtual void Update();

        /**
        * Moves the player forward with maximum acceleration.
        */
        void Forward();

        /**
        * Just apply a turning force.
        */
        void TurnRight();

        /**
        * Just apply a turning force.
        */
        void TurnLeft();

        /**
        * Check to see the player is on the floor (to prevent jumping on the ground)
        * Uses the code from the earlier ray casting example.
        *
        */
        bool IsGrounded();

        /**
        *  Jump
        *
        */
        void Jump();

        /**
        * Fly
        *
        */
        void Fly();

    };
}

#endif