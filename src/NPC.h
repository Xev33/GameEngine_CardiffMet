#ifndef NPC_
#define NPC_

#include "GameObject.h"
#include "ComponentFactory.h"
#include "AComponent.h"
#include "Rigibodies.h"

namespace XDGameEngine
{
    class NPC : public GameObject
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

        /**
        * The target the npc wants to reach
        */
        btTransform m_target;

        /**
        * All the target the npc can have and will swap between
        */
        std::vector<btTransform> m_patrolWayPoints;
        
        /**
        * The vector index tracker
        */
        int currentWaypoint;

        /**
        * The npc's health
        */
        int m_health;

    public:
        NPC(const btVector3 pos = btVector3(1.0f, 1.0f, 1.0f),
            const btQuaternion rot = btQuaternion(0.0f, 0.0f, 0.0f),
            const btVector3 scale = btVector3(1.0f, 1.0f, 1.0f));
        ~NPC();

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

        /**
        * Adda new patrol waypoint
        */
        void AddWayPoint(btVector3 newPoint) noexcept;

    };
}

#endif