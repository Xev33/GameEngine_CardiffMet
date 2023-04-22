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
#include "Scene.h"
#include "Input.h"

#include "OgreBullet.h"

Game::Game() : ApplicationContext("The Forsaken - st0242612")
{
    // Set the Input singleton
    //inpMgr = XDGameEngine::Input::Instance();

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

    createBasicScene();
    loadScene(currentScene);

}

void Game::createBasicScene()
{
    if (currentScene != nullptr)
        unloadCurrentScene();

    currentScene = new XDGameEngine::Scene();
    currentScene->setup(getRoot(), getRenderWindow());
}

void Game::loadScene(XDGameEngine::Scene* scene)
{
    if (scene == nullptr)
        return;

    // Set all the Ogre stuff from the current scene in case we need to get them later
    scnMgr = scene->getSceneManager();

    // Same for bullet
    btDefaultCollisionConfiguration* collisionConfiguration = scene->getCollisionConfiguration();
    btCollisionDispatcher* dispatcher = scene->getDispatcher();
    btBroadphaseInterface* overlappingPairCache = scene->getOverlappingPairCache();
    btSequentialImpulseConstraintSolver* solver = scene->getSolver();
    btDiscreteDynamicsWorld* dynamicsWorld = scene->getDynamicWorld();
}

void Game::unloadCurrentScene()
{
    dynamicsWorld = nullptr;

    solver = nullptr;

    overlappingPairCache = nullptr;

    dispatcher = nullptr;

    collisionConfiguration = nullptr;

    if (currentScene != nullptr)
        delete currentScene;
    currentScene = nullptr;
}

bool Game::frameStarted(const Ogre::FrameEvent &evt)
{
    // Be sure to call base class - otherwise events are not polled.
    ApplicationContext::frameStarted(evt);
    currentScene->updateFrameStarted(evt);
    return true;
}

bool Game::frameEnded(const Ogre::FrameEvent &evt)
{
    currentScene->updateFrameEnded(evt);
    return true;
}

/* Uses the OgreBites::InputListener, but can also use
   SDL2 */
bool Game::keyPressed(const KeyboardEvent& evt)
{
    // MAKE A INPUT MANAGER SINGLETON to allow everyone to access it
    XDGameEngine::Input::Instance().InputPressed(evt);
    //inpMgr.InputPressed(evt);
    std::cout << "Got key down event" << std::endl;

    // The only gameInput -> Escape = stop the game
    if (evt.keysym.sym == SDLK_ESCAPE)
    {
        getRoot()->queueEndRendering();
    }

    return true;
}

bool Game::keyReleased(const KeyboardEvent& evt)
{
    std::cout << "Got key up event" << std::endl;
    XDGameEngine::Input::Instance().InputReleased(evt);
    //inpMgr.InputReleased(evt);

    return true;
}

bool Game::mouseMoved(const MouseMotionEvent& evt)
{
	//std::cout << "Got Mouse" << std::endl;
	return true;
}