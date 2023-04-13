/*-------------------------------------------------------------------------
Significant portions of this project are based on the Ogre Tutorials
- https://ogrecave.github.io/ogre/api/1.10/tutorials.html
Copyright (c) 2000-2013 Torus Knot Software Ltd

Manual generation of meshes from here:
- http://wiki.ogre3d.org/Generating+A+Mesh

Ogre / Bullet connectivity from here:
 https://oramind.com/ogre-bullet-a-beginners-basic-guide/

*/

#include <exception>
#include <iostream>

#include "Game.h"

#include "OgreBullet.h"

#include "Player.h"
#include "NPC.h"

Game::Game() : ApplicationContext("The Forsaken - st0242612")
{
    // Set all the Ogre stuff to nullptr - trap uninitialised pointer errors.
    scnMgr = nullptr;

    currentScene = nullptr;

    // Same for bullet
    btDefaultCollisionConfiguration *collisionConfiguration = nullptr;
    btCollisionDispatcher *dispatcher = nullptr;
    btBroadphaseInterface *overlappingPairCache = nullptr;
    btSequentialImpulseConstraintSolver *solver = nullptr;
    btDiscreteDynamicsWorld *dynamicsWorld = nullptr;

    // keys

    aDown = dDown = wDown = fDown = jDown = false;

}

Game::~Game()
{
    dynamicsWorld = nullptr;

    solver = nullptr;

    overlappingPairCache = nullptr;

    dispatcher = nullptr;

    collisionConfiguration = nullptr;

    currentScene = nullptr;
}

void Game::setup()
{
    // do not forget to call the base first
    ApplicationContext::setup();

    addInputListener(this);

    Root* root = getRoot();

    //currentScene->setup(getRoot());
    currentScene = new XDGameEngine::Scene();
    currentScene->setup(getRoot(), getRenderWindow());

}

bool Game::frameStarted(const Ogre::FrameEvent &evt)
{
    // Be sure to call base class - otherwise events are not polled.
    ApplicationContext::frameStarted(evt);
    btDiscreteDynamicsWorld* dynamicsWorld = currentScene->getDynamicWorld();
    Player* player = currentScene->getPlayer();

    if (dynamicsWorld != NULL)
    {
        // Bullet can work with a fixed timestep
         dynamicsWorld->stepSimulation(1.f / 60.f, 10);

        // Or a variable one, however, under the hood it uses a fixed timestep
        // then interpolates between them.

        // Apply forces based on input. 
        if(wDown)
            player->forward();
        
        if(aDown)
            player->turnRight();

        if(dDown)
            player->turnLeft();

        if(jDown)
            player->jump();

        if(fDown)
            player->fly();


        dynamicsWorld->stepSimulation((float)evt.timeSinceLastFrame, 10);

        // update positions of all objects
        for (int j = dynamicsWorld->getNumCollisionObjects() - 1; j >= 0; j--)
        {
            btCollisionObject *obj = dynamicsWorld->getCollisionObjectArray()[j];
            btRigidBody *body = btRigidBody::upcast(obj);
            btTransform trans;

            if (body && body->getMotionState())
            {
                body->getMotionState()->getWorldTransform(trans);

                // Bullet has updated the rididbody, we now need to update the ogre scene node (i.e. the model on screen).
                void *userPointer = body->getUserPointer();

                // This is a horrific hack!!!!!!
                // Need to change this so everything in the game (including the floor) uses 
                // the same method of updating its physics / graphics. 
                if (userPointer && userPointer != currentScene->getPlayer() && userPointer != currentScene->getNPC())
                {
                    btQuaternion orientation = trans.getRotation();
                    Ogre::SceneNode *sceneNode = static_cast<Ogre::SceneNode *>(userPointer);
                    sceneNode->setPosition(Ogre::Vector3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ()));
                    sceneNode->setOrientation(Ogre::Quaternion(orientation.getW(), orientation.getX(), orientation.getY(), orientation.getZ()));
                }
                else
                {
                     //std::cout << "Player update" << std::endl;
                     currentScene->getPlayer()->update();


                }
            }
            else
            {
                trans = obj->getWorldTransform();
            }
        }

        // always update the npc, it has no player input to wake it back up!

        currentScene->getNPC()->update();

       
    }

        return true;
}

    bool Game::frameEnded(const Ogre::FrameEvent &evt)
    {
        btDiscreteDynamicsWorld* dynamicsWorld = currentScene->getDynamicWorld();
        if (this->dynamicsWorld != NULL)
        {
            // Bullet can work with a fixed timestep
             dynamicsWorld->stepSimulation(1.f / 60.f, 10);

            // Or a variable one, however, under the hood it uses a fixed timestep
            // then interpolates between them.

            dynamicsWorld->stepSimulation((float)evt.timeSinceLastFrame, 10);
        }
        return true;
    }

/* Uses the OgreBites::InputListener, but can also use
   SDL2 */
bool Game::keyPressed(const KeyboardEvent& evt)
{
    std::cout << "Got key down event" << std::endl;
    if (evt.keysym.sym == SDLK_ESCAPE)
    {
        getRoot()->queueEndRendering();
    }

    if(evt.keysym.sym == 'w')
    {
        wDown = true;
    }

    if(evt.keysym.sym == 'a')
    {
        aDown = true;
    }

    if(evt.keysym.sym == 'd')
    {
        dDown = true;
    }

    if(evt.keysym.sym == 'j')
    {
        jDown = true;
    }

     if(evt.keysym.sym == 'f')
    {
        fDown = true;
    }

    return true;
}

bool Game::keyReleased(const KeyboardEvent& evt)
{
    std::cout << "Got key up event" << std::endl;

    if(evt.keysym.sym == 'w')
    {
        wDown = false;
    }

    if(evt.keysym.sym == 'a')
    {
        aDown = false;
    }

    if(evt.keysym.sym == 'd')
    {
        dDown = false;
    }

    if(evt.keysym.sym == 'j')
    {
        jDown = false;
    }

     if(evt.keysym.sym == 'f')
    {
        fDown = false;
    }

    return true;
}

bool Game::mouseMoved(const MouseMotionEvent& evt)
{
	//std::cout << "Got Mouse" << std::endl;
	return true;
}

