#ifndef PLAYER_
#define PLAYER_

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
        RigidBody* body;

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