#ifndef XDPLAYER_
#define XDPLAYER_

#include "GameObject.h"
#include "ComponentFactory.h"
#include "AComponent.h"
#include "Rigibodies.h"

namespace XDGameEngine
{
    class XDPlayer : public XDGameEngine::GameObject
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

        // Patrol variables
        btTransform m_target;
        btTransform patrolWayPoints[3];
        int currentWaypoint;

    public:
        XDPlayer();
        ~XDPlayer();

        virtual void Update();

        /**
        * Moves the player forward with maximum acceleration.
        */
        void Forward();

        /**
        * Just apply a turning force.
        */
        void TurnRightScaled(float scalar);


        /**
        * Just apply a turning force.
        */
        void TurnLeftScaled(float scalar);

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

        /**
         * @brief Target for arrive.
         */
        void SetTarget(btTransform target);

        /**
        * @brief Arrive behaviour, heads towards a target held in the class.
        */
        void Arrive();

        /**
        * @brief support method for arrive, look where you are going.
        * @return true if we're looking the right way, false otherwise (keep turning).
        */
        bool LookWhereYouAreGoing();

        /**
        * @brief Check target is in range, allows re-use for slowing radius.
        * @param range distance to target.
        */
        bool TargetInRange(float range);

    };
}

#endif