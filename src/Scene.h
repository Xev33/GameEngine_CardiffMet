#ifndef SCENE_
#define SCENE_

#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include "OgreCameraMan.h"
/* Bullet3 Physics */
#include "btBulletDynamicsCommon.h"
#include "btBulletCollisionCommon.h"

class Player;
class NPC;

namespace XDGameEngine
{
	class Scene
	{
	private:
        /**
        * Ogre Scene Manager.
        */
        Ogre::SceneManager* scnMgr;

        /**
         * Collision configuration.
         */
        btDefaultCollisionConfiguration* collisionConfiguration;

        /**
        * The default collision dispatcher. For parallel processing you can use a different dispatcher (see Extras/BulletMultiThreaded)
        */
        btCollisionDispatcher* dispatcher;

        /**
        * btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
        */
        btBroadphaseInterface* overlappingPairCache;

        /**
        * The default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
        */
        btSequentialImpulseConstraintSolver* solver;

        /**
        * The dynamics world (physics/collision world).
        */
        btDiscreteDynamicsWorld* dynamicsWorld;

        /**
        * Keep track of the shapes, we release memory at exit.
        * make sure to re-use collision shapes among rigid bodies whenever possible!
        */
        btAlignedObjectArray<btCollisionShape*> collisionShapes;

        /**
        * The Player object
        */
        Player* player;

        /**
         * The NPC object
         */
        NPC* npc;

    public:
        /**
        * Creates the object, sets all pointers to nullptr.
        */
        Scene();

        /**
        * Destructor (virtual), as this is virtual that of the sub class will also be called.
        */
        virtual ~Scene();

        ////-----------------------------------------------------------------------
        //// ALL SETUP FONCTION TO REMOVE------------------------------------------
        ////-----------------------------------------------------------------------

        /**
        * Carries out all setup, includes lighting, scene objects.
        */;
        void setup(Ogre::Root* root);

        /**
        * Sets up the bullet environment
        */
        void bulletInit();

        ///**
        //* Sets up the camera
        //*/
        //void setupCamera();

        ///**
        //* Quick and dirty box mesh, essentially this is a mix of the Ogre code to setup a box - from example.
        //* Added to this is the setup for the bullet3 collision box and rigid body.
        //*/
        //void setupBoxMesh();

        ///**
        //* Player setup
        //*/
        //void setupPlayer();

        ///**
        //* NPC setup
        //*/
        //void setupNPC();

        ///**
        //* Turns on on the coffee machine.
        //*/
        //void setupFloor();

        ///**
        //* Creates, lights and adds them to the scene.  All based on the sample code, needs moving out into a level class.
        //*/
        //void setupLights();
	};
}

#endif