#ifndef PLAYER_
#define PLAYER_

#include "GameObject.h"
#include "ComponentFactory.h"
#include "AComponent.h"
#include "Rigibodies.h"

namespace XDGameEngine
{
    class Player : public GameObject
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
        Player(const btVector3 pos = btVector3(1.0f, 1.0f, 1.0f),
            const btQuaternion rot = btQuaternion(0.0f, 0.0f, 0.0f),
            const btVector3 scale = btVector3(1.0f, 1.0f, 1.0f));
        ~Player();

        virtual void Update();

        /**
        * Moves the player forward with maximum acceleration.
        */
        void Forward();

        /**
        * Moves the player forward with maximum acceleration.
        */
        void Backward();

        /**
        * Just apply a turning force.
        */
        void TurnRight();

        /**
        * Just apply a turning force.
        */
        void TurnLeft();

        /**
        * Just apply a turning force.
        */
        void StraffRight();

        /**
        * Just apply a turning force.
        */
        void StraffLeft();

        /**
        * Just apply a turning force.
        */
        void Fire();


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