#ifndef RigidBody_
#define RigidBody_

#include "AComponent.h"
#include "btBulletDynamicsCommon.h"

namespace XDGameEngine
{
    class RigidBody : public AComponent
    {
    protected:
    private:
        btDiscreteDynamicsWorld* m_dynamicsWorld;

        btRigidBody* m_rigidbody; /**< The rigidbody itself */
        btCollisionShape* m_colShape;  /**< Collision shape, describes the collision boundary */

        btScalar m_mass; /**< The body mass. 0 = static mesh */
        btScalar m_linearDamping; /**< Damping force on the linear motion of the body, kind of air/friction */
        btScalar m_angularDamping; /**< Damping force on the angular motion of the body, kind of air/friction */
        bool m_isDynamic;

        // these values should have help to disable the component
        // without removing it from the dynamic world but it doesn't work
        // and I don't have more time to spend on that
        //btVector3 m_prevVelocity;
        //btVector3 m_prevPosition;
        //btQuaternion m_prevRotation;

    public:
        RigidBody();
        ~RigidBody();

        /**
        * Overrided method from AComponent. Connect the component to the dynamicWorld
        */
        virtual void SetUpComponent(GameObject& go) final;
        
        /**
        * Toggle the rigidbody in the dynamic world
        */
        virtual void SetActive(bool isActive) final;

        /**
        * Update the colliding position and update the gameObject's transform
        */
        virtual void UpdateComponent(GameObject& go) final;

        void SetUserPointer(void* userPointer);

        /**
        * Set body's mass
        */
        void SetMass(float mass) noexcept;

        /**
        * Section to set the body's friction
        */
        void SetLinearDamping(float linearDamping) noexcept;

        /**
        * Section to set the body's friction
        */
        void SetAngularDamping(float angularDamping) noexcept;

        /**
        * Rigidbody setter
        */
        void SetRigidBody(btRigidBody* body) noexcept;

        /**
        * Getter for the body's mass
        */
        float GetMass() const noexcept;
        
        /**
        * Getter for the LinearDamping
        */
        float GetLinearDamping() const noexcept;

        /**
        * Getter for the AnfularDamping
        */
        float GetAngularDamping() const noexcept;

        /**
        * Getter for the rigidbody
        */
        btRigidBody* GetRigidbody() noexcept;

        /**
        * Return if the body is dynamic or not
        */
        bool IsDynamic() const noexcept;

        /**
        * Check to see the player is on the floor (to prevent jumping on the ground)
        * Uses the code from the earlier ray casting example.
        */
        bool IsGrounded() const noexcept;

        /*
        * Check if the solid body enter in a collision and retrieve the collision obj tag
        */
        uint32_t OnCollisionEnter(uint32_t tag) const noexcept;
    };
}

#endif