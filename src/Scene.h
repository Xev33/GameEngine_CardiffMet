#ifndef SCENE_
#define SCENE_

#include <vector>
#include <memory>

#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include "OgreCameraMan.h"
/* Bullet3 Physics */
#include "btBulletDynamicsCommon.h"
#include "btBulletCollisionCommon.h"
#include "BulletCollision/CollisionDispatch/btGhostObject.h"

class Player;
class NPC;

namespace XDGameEngine
{
    class GameObject;
}

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
         * The viewport
         */
        Ogre::RenderWindow* rw;

        /**
        * The vector containing all gameobjects
        */
        std::vector<std::unique_ptr<GameObject>> m_go;


    public:
        /**
        * Creates the object, sets all pointers to nullptr.
        */
        Scene();

        /**
        * Destructor (virtual), as this is virtual that of the sub class will also be called.
        */
        virtual ~Scene();

        /**
        * Get the game update when the frame starts
        */
        void updateFrameStarted(const Ogre::FrameEvent& evt);

        /**
        * Get the game update when the frame ends
        */
        void updateFrameEnded(const Ogre::FrameEvent& evt);


        //-----------------------------------------------------------------------
        // ALL SETUP FONCTIONS --------------------------------------------------
        //-----------------------------------------------------------------------

        /**
        * Carries out all setup, includes lighting, scene objects.
        */;
        void setup(Ogre::Root* root, Ogre::RenderWindow* nvp);

        /**
        * Sets up the bullet environment
        */
        void bulletInit();

        /**
        * Sets up the camera
        */
        void setupCamera();

        /**
        * Creates player and npcs.
        */
        void setupStaticObj() noexcept;

        /**
        * Creates cube for the level's blockout and the lights for the demonstration
        */
        void setupMovingObj() noexcept;


        //-----------------------------------------------------------------------
        // GETTERS --------------------------------------------------------------
        //-----------------------------------------------------------------------

        Ogre::SceneManager*                     getSceneManager() { return scnMgr; }
        btDefaultCollisionConfiguration*        getCollisionConfiguration() { return collisionConfiguration; }
        btCollisionDispatcher*                  getDispatcher() { return dispatcher; }
        btBroadphaseInterface*                  getOverlappingPairCache() { return overlappingPairCache; }
        btSequentialImpulseConstraintSolver*    getSolver() { return solver; }
        btDiscreteDynamicsWorld* getDynamicWorld() { return dynamicsWorld; }
        btAlignedObjectArray<btCollisionShape*>*                getCollisionShapes() { return &collisionShapes; }
        void UseInputTest();
	};

    /*
    * The class who creates an output of two colliding objects
    * This class has been inspired by someone's else here:
    * https://stackoverflow.com/questions/20300615/bullet-collision-callback-between-2-bodies
    */
    class MyContactResultCallback : public btCollisionWorld::ContactResultCallback
    {
    public:
        bool hitObject = false;

        virtual btScalar addSingleResult(btManifoldPoint& cp,
            const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0,
            const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1) override
        {
            // If we've found a contact, set the flag and return 0 (which means we want to stop processing contacts)
            hitObject = true;
            return 0;
        }
    };
}

#endif