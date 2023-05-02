#include "Player.h"
#include "MeshRenderer.h"
#include "Rigibodies.h"
#include "Input.h"
#include "Game.h"
#include "Scene.h"

namespace XDGameEngine
{
    Player::Player(const btVector3 pos, const btQuaternion rot, const btVector3 scale) :
        GameObject(pos, rot, scale)
    {
        m_forwardForce = -0.5f;
        m_turningForce = 50.0f;
        m_jumpForce = 1.0f;

        m_linearDamping = 2.6f;
        m_angularDamping = 0.6f;

        m_tag = 'PLYR';

        AddComponent(XDGameEngine::ComponentFactory::CreateComponent('MSRD', *this));
        AddComponent(XDGameEngine::ComponentFactory::CreateComponent('BXCS', *this));
        AddComponent(XDGameEngine::ComponentFactory::CreateComponent('RGBD', *this));
        this->GetComponent<MeshRenderer>()->SetMeshFileName("cube.mesh");

        body = this->GetComponent<RigidBody>();

        SetupAllComponents();
        m_rgbd = GetComponent<RigidBody>()->GetRigidbody();
        m_rgbd->setDamping(m_linearDamping, m_angularDamping);
        m_rgbd->setUserPointer(&m_tag);
    }

    Player::~Player()
    {
        m_shouldBeUpdated = true;
        m_transform = nullptr;
        m_rgbd = nullptr;
    }

    void Player::Update()
    {
        // Or a variable one, however, under the hood it uses a fixed timestep
        // then interpolates between them.

        // Apply forces based on input.
        if (m_rgbd && m_rgbd->getMotionState())
        {
            //m_transform->setRotation(btQuaternion(0, m_transform->getRotation().getY(), 0));
            if (XDGameEngine::Input::Instance().GetKeyDown("w"))
                Forward();

            if (XDGameEngine::Input::Instance().GetKeyDown("s"))
                Backward();

            if (XDGameEngine::Input::Instance().GetKeyDown("d"))
                StraffRight();

            if (XDGameEngine::Input::Instance().GetKeyDown("a"))
                StraffLeft();

            if (XDGameEngine::Input::Instance().GetKeyDown("leftArrow"))
                TurnRight();

            if (XDGameEngine::Input::Instance().GetKeyDown("rightArrow"))
                TurnLeft();

            if (XDGameEngine::Input::Instance().GetKeyDown("space"))
                Fly();

            if (XDGameEngine::Input::Instance().GetKeyDown("j"))
                Jump();

            if (XDGameEngine::Input::Instance().GetKeyDown("f"))
                Fire();

        }

    }

    void Player::Forward()
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

    void Player::Backward()
    {
        //Create a vector in local coordinates
        //pointing down z.
        btVector3 fwd(0.0f, 0.0f, -m_forwardForce);
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

    void Player::TurnRight()
    {
        //Apply a turning force to the front of the m_rgbd.
        btVector3 right(0.0f, m_turningForce, 0.0f);

        if (m_rgbd && m_rgbd->getMotionState())
        {
            //better - only turn if we're moving.
            //not ideal, if sliding sideways will keep turning.
            //if(m_rgbd->getLinearVelocity().length() > 0.0f)
            m_rgbd->applyTorqueImpulse(right);
        }
    }

    void Player::TurnLeft()
    {
        //Apply a turning force to the front of the m_rgbd.
        btVector3 left(0.0f, -m_turningForce, 0.0f);

        if (m_rgbd && m_rgbd->getMotionState())
        {
            //better - only turn if we're moving.
            //not ideal, if sliding sideways will keep turning.
           // if(m_rgbd->getLinearVelocity().length() > 0.0f)
            m_rgbd->applyTorqueImpulse(left);
        }
    }

    void Player::StraffRight()
    {
        //Create a vector in local coordinates
        //pointing down z.
        btVector3 rgt(-m_forwardForce, 0.0f, 0.0f);
        btVector3 push;

        btTransform trans;

        if (m_rgbd && m_rgbd->getMotionState())
        {
            //get the orientation of the rigid m_rgbd in world space.
            m_rgbd->getMotionState()->getWorldTransform(trans);
            btQuaternion orientation = trans.getRotation();

            //rotate the local force, into the global space.
            //i.e. push in down the local z.
            push = quatRotate(orientation, rgt);

            //activate the m_rgbd, this is essential if the m_rgbd
            //has gone to sleep (i.e. stopped moving/colliding).
            m_rgbd->activate();

            //apply a force to the center of the m_rgbd
            m_rgbd->applyCentralImpulse(push);
        }
    }

    void Player::StraffLeft()
    {
        //Create a vector in local coordinates
        //pointing down z.
        btVector3 rgt(m_forwardForce, 0.0f, 0.0f);
        btVector3 push;

        btTransform trans;

        if (m_rgbd && m_rgbd->getMotionState())
        {
            //get the orientation of the rigid m_rgbd in world space.
            m_rgbd->getMotionState()->getWorldTransform(trans);
            btQuaternion orientation = trans.getRotation();

            //rotate the local force, into the global space.
            //i.e. push in down the local z.
            push = quatRotate(orientation, rgt);

            //activate the m_rgbd, this is essential if the m_rgbd
            //has gone to sleep (i.e. stopped moving/colliding).
            m_rgbd->activate();

            //apply a force to the center of the m_rgbd
            m_rgbd->applyCentralImpulse(push);
        }

    }

    void Player::Jump()
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

    void Player::Fire()
    {
    }

    void Player::Fly()
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
}