#include "XDPlayer.h"

#include "MeshRenderer.h"
#include "Rigibodies.h"

#include "Input.h"
#include "Game.h"
#include "Scene.h"

#define _USE_MATH_DEFINES
#include <math.h>

namespace XDGameEngine
{
    XDPlayer::XDPlayer(const btVector3 pos, const btQuaternion rot, const btVector3 scale) :
        GameObject(pos, rot, scale)
    {
        m_forwardForce = 5.0f;
        m_turningForce = 100.0f;
        m_jumpForce = 5.0f;

        m_linearDamping = 0.6f;
        m_angularDamping = 0.8f;

        AddComponent(XDGameEngine::ComponentFactory::CreateComponent('MSRD', *this));
        AddComponent(XDGameEngine::ComponentFactory::CreateComponent('BXCS', *this));
        AddComponent(XDGameEngine::ComponentFactory::CreateComponent('RGBD', *this));
        this->GetComponent<MeshRenderer>()->SetMeshFileName("cube.mesh");
        body = this->GetComponent<RigidBody>();

        SetupAllComponents();

        m_rgbd = GetComponent<RigidBody>()->GetRigidbody();
        m_rgbd->setDamping(m_linearDamping, m_angularDamping);

        btTransform target1;
        btTransform target2;
        btTransform target3;
        target1.setOrigin(btVector3(200.0f, 80.0f, 200.0f));
        target2.setOrigin(btVector3(-200.0f, 80.0f, 200.0f));
        target3.setOrigin(btVector3(200.0f, 80.0f, -400.0f));

        patrolWayPoints[0] = target1;
        patrolWayPoints[1] = target2;
        patrolWayPoints[2] = target3;
        currentWaypoint = 0;
        SetTarget(patrolWayPoints[currentWaypoint]);
    }

    XDPlayer::~XDPlayer()
    {
        m_shouldBeUpdated = true;
        m_transform = nullptr;
        m_rgbd = nullptr;
    }

    void XDPlayer::Update()
    {
        /* AI here */
        Arrive();
    }

    void XDPlayer::Forward()
    {
        //Create a vector in local coordinates
        //pointing down z.
        btVector3 fwd(0.0f, 0.0f, m_forwardForce);
        btVector3 push;

        btTransform trans;

        if (m_rgbd && m_rgbd->getMotionState())
        {
            //get the orientation of the rigid m_rgbd in world space.
            m_rgbd->getMotionState()->getWorldTransform(trans);
            btQuaternion orientation = trans.getRotation();

            //rotate the local force, into the global space.
            //i.e. push in down the local z.
            push = quatRotate(orientation, fwd);

            //activate the m_rgbd, this is essential if the m_rgbd
            //has gone to sleep (i.e. stopped moving/colliding).
            m_rgbd->activate();

            //apply a force to the center of the m_rgbd
            m_rgbd->applyCentralImpulse(push);
        }
    }

    void XDPlayer::TurnRightScaled(float scalar)
    {
        //Apply a turning force to the front of the body.
        float tf = m_turningForce;
        tf *= scalar;
        btVector3 right(0.0f, tf, 0.0f);
        btVector3 turn;

        btTransform trans;

        if (m_rgbd && m_rgbd->getMotionState())
        {
            //activate the body, this is essential if the body
            //has gone to sleep (i.e. stopped moving/colliding).
            m_rgbd->activate();

            //better - only turn if we're moving.
            //not ideal, if sliding sideways will keep turning.
           // if(body->getLinearVelocity().length() > 0.0f)
            m_rgbd->applyTorqueImpulse(right);
        }
    }

    void XDPlayer::TurnLeftScaled(float scalar)
    {
        //Apply a turning force to the front of the body.
        float tf = -m_turningForce;
        tf *= scalar;
        btVector3 left(0.0f, tf, 0.0f);
        btVector3 turn;

        btTransform trans;

        if (m_rgbd && m_rgbd->getMotionState())
        {
            //activate the body, this is essential if the body
            //has gone to sleep (i.e. stopped moving/colliding).
            m_rgbd->activate();

            //better - only turn if we're moving.
            //not ideal, if sliding sideways will keep turning.
           // if(body->getLinearVelocity().length() > 0.0f)
            m_rgbd->applyTorqueImpulse(left);
        }
    }

    void XDPlayer::Jump()
    {
        //Create a vector in local coordinates
        //pointing up.
        btVector3 up(0.0f, m_jumpForce, 0.0f);

        if (m_rgbd && m_rgbd->getMotionState() && body->IsGrounded())
        {
            // Turn off linear damping or we float back down.
            m_rgbd->setDamping(0.0f, m_angularDamping);


            //activate the m_rgbd, this is essential if the m_rgbd
            //has gone to sleep (i.e. stopped moving/colliding).
            m_rgbd->activate();

            //apply a force to the center of the m_rgbd
            m_rgbd->applyCentralImpulse(up);
        }
    }

    void XDPlayer::Fly()
    {
        //Create a vector in local coordinates
        //pointing up.
        btVector3 up(0.0f, m_jumpForce, 0.0f);
        btVector3 push;

        if (m_rgbd && m_rgbd->getMotionState())
        {

            //activate the m_rgbd, this is essential if the m_rgbd
            //has gone to sleep (i.e. stopped moving/colliding).
            m_rgbd->activate();

            //apply a force to the center of the m_rgbd
            m_rgbd->applyCentralImpulse(up);
        }
    }

    void XDPlayer::SetTarget(btTransform target)
    {
        this->m_target = target;
    }

    void XDPlayer::Arrive()
    {
        // Slowing radius
        float slowingRad = 500.0f;
        // Stopping radius
        float stoppingRad = 105.0f; // note cube is 100 square, don't set this below 100!

        if (TargetInRange(stoppingRad))
        {


            currentWaypoint++;
            if (currentWaypoint >= 3)
                currentWaypoint = 0;
            SetTarget(patrolWayPoints[currentWaypoint]);
            // stop the npc!
        }
        else
        {
            if (LookWhereYouAreGoing())
            {
                // point at the player and ram, could make a fun sumo game out of this!
                Forward();

                // Aim to slow to a stop at the position
                if (TargetInRange(slowingRad))
                {
                    // slow to target
                }

            }
            else
            {

            }
        }

    }

    bool XDPlayer::LookWhereYouAreGoing()
    {
        // Current Orientation
        btTransform trans;
        m_rgbd->getMotionState()->getWorldTransform(trans);
        btQuaternion orientation = trans.getRotation();

        // Desired force
        btVector3 forward(0.0f, 0.0f, 1.0f);

        //rotate the local forward, into the global space.
        //i.e. push in down the local z.
        forward = quatRotate(orientation, forward);
        forward.normalize();

        btVector3 vecToTarget = m_target.getOrigin() - trans.getOrigin();
        vecToTarget.normalize();

        float dotProd = btDot(forward, vecToTarget); // dotprod
        float angle = acos(dotProd);

        btVector3 crossProd = btCross(forward, vecToTarget); // cross prod

        if (angle < 0.3f) // dead ahead! - ore close enough
            return true;
        else
        {
            if (crossProd.y() > 0.0f)
            {
                TurnRightScaled(angle / M_PI);
            }
            else
            {
                TurnLeftScaled(angle / M_PI);
            }
        }

        return false;
    }

    bool XDPlayer::TargetInRange(float range)
    {
        btTransform trans;
        float range2 = range * range; // faster than working out the root of the lenght?

        // Get current transform. 
        m_rgbd->getMotionState()->getWorldTransform(trans);

        btVector3 vecToTarget = m_target.getOrigin() - trans.getOrigin();

        if (vecToTarget.length2() < range2)
            return true;
        else
            return false;
    }
}