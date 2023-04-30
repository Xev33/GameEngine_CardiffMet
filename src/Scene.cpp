#include "Scene.h"
#include "Input.h"

#include "Player.h"
#include "NPC.h"
#include "GOTest.h"
#include "Rigibodies.h"
#include "Transform.h"
#include <iostream>

#include "XDPlayer.h"
#include "CollisionShape.h"
#include "MeshRenderer.h"
#include "OgreBullet.h"

#include <memory>

namespace XDGameEngine
{
    Scene::Scene()
    {
         //Set all the Ogre stuff to nullptr - trap uninitialised pointer errors.
        scnMgr = nullptr;

        // Same for bullet
        btDefaultCollisionConfiguration* collisionConfiguration = nullptr;
        btCollisionDispatcher* dispatcher = nullptr;
        btBroadphaseInterface* overlappingPairCache = nullptr;
        btSequentialImpulseConstraintSolver* solver = nullptr;
        btDiscreteDynamicsWorld* dynamicsWorld = nullptr;

        // npc 
        npc = nullptr;

    }

    Scene::~Scene()
    {
        // cleanup in the reverse order of creation/initialization

        // remove the rigidbodies from the dynamics world and delete them

        for (int i = dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--)
        {
            btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
            btRigidBody* body = btRigidBody::upcast(obj);

            if (body && body->getMotionState())
            {
                delete body->getMotionState();
            }

            dynamicsWorld->removeCollisionObject(obj);
            delete obj;
        }

        // delete collision shapes
        for (int j = 0; j < collisionShapes.size(); j++)
        {
            btCollisionShape* shape = collisionShapes[j];
            collisionShapes[j] = 0;
            delete shape;
        }

        // delete dynamics world
        delete dynamicsWorld;
        dynamicsWorld = nullptr;

        // delete solver
        delete solver;
        solver = nullptr;

        // delete broadphase
        delete overlappingPairCache;
        overlappingPairCache = nullptr;

        // delete dispatcher
        delete dispatcher;
        dispatcher = nullptr;

        delete collisionConfiguration;
        collisionConfiguration = nullptr;

        // next line is optional: it will be cleared by the destructor when the array goes out of scope
        collisionShapes.clear();
    }

    void Scene::updateFrameStarted(const Ogre::FrameEvent& evt)
    {
        if (dynamicsWorld != NULL)
        {
            // Bullet can work with a fixed timestep
            dynamicsWorld->stepSimulation(1.f / 60.f, 10);

            // Update all game objects that need to be updated
            for (auto& it = m_go.begin(); it != m_go.end();)
            {
                auto go = it->get();

                // Delete every gameObject properly
                if (go->ShouldBeDestroy() == true)
                    m_go.erase(it);
                else
                {
                    if (go->IsActive() == true)
                    {
                        go->Update();
                        go->UpdateComponents();
                    }
                    ++it;
                }
            }

            dynamicsWorld->stepSimulation((float)evt.timeSinceLastFrame, 10);
            //npc->update();
        }
    }

    void Scene::updateFrameEnded(const Ogre::FrameEvent& evt)
    {
        UseInputTest();
        if (this->dynamicsWorld != NULL)
        {
            // Bullet can work with a fixed timestep
            dynamicsWorld->stepSimulation(1.f / 60.f, 10);

            // Or a variable one, however, under the hood it uses a fixed timestep
            // then interpolates between them.

            dynamicsWorld->stepSimulation((float)evt.timeSinceLastFrame, 10);
        }
    }


    ////-----------------------------------------------------------------------
    //// ALL SETUP FONCTION TO REMOVE------------------------------------------
    ////-----------------------------------------------------------------------


    void Scene::setup(Ogre::Root* root, Ogre::RenderWindow* nrw)
    {
        rw = nrw;
        // get a pointer to the already created root
        scnMgr = root->createSceneManager();

        // register our scene with the RTSS
        Ogre::RTShader::ShaderGenerator* shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
        shadergen->addSceneManager(scnMgr);

        bulletInit();

        auto p = std::make_unique<Player>();
        auto d = std::make_unique<XDPlayer>();
        m_go.push_back(std::move(p));
        m_go.push_back(std::move(d));

        setupCamera();

        setupFloor();

        setupLights();

        //setupNPC();
    }

    void Scene::bulletInit()
    {
        /// collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
        collisionConfiguration = new btDefaultCollisionConfiguration();

        /// use the default collision dispatcher. For parallel processing you can use a different dispatcher (see Extras/BulletMultiThreaded)
        dispatcher = new btCollisionDispatcher(collisionConfiguration);

        /// btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
        overlappingPairCache = new btDbvtBroadphase();

        /// the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
        solver = new btSequentialImpulseConstraintSolver;

        dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);

        dynamicsWorld->setGravity(btVector3(0, -10, 0));
    }

    void Scene::setupCamera()
    {
        // Create Camera
        Ogre::Camera* cam = scnMgr->createCamera("myCam");

        // Setup Camera
        cam->setNearClipDistance(5);

        // Position Camera - to do this it must be attached to a scene graph and added
        // to the scene.
        Ogre::SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
        camNode->setPosition(200, 300, 600);
        camNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TransformSpace::TS_WORLD);
        camNode->attachObject(cam);

        // Setup viewport for the camera.
        // I SHOULD PROBABLY MOVE THE VIEWPORT TO THE GAME CLASS
        Ogre::Viewport* vp = rw->addViewport(cam);
        vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));

        // link the camera and view port.
        cam->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
    }

    /**
     * @brief Create a NPC using the player class.
     *
     */
    void Scene::setupNPC()
    {
        // box mass.
        float mass = 1.0f;

        // Axis
        Vector3 axis(1.0, 0.0, 0.0);
        axis.normalise();

        // angle
        Radian rads(Degree(0.0));

        npc = new NPC();
        npc->setup(scnMgr, dynamicsWorld, mass);
        npc->setRotation(axis, rads);
        npc->setPosition(-500.0f, 80.0f, 500.0f);

        collisionShapes.push_back(npc->getCollisionShape());
        dynamicsWorld->addRigidBody(npc->getRigidBody());

        btTransform target;
        target.setOrigin(btVector3(200.0f, 80.0f, 200.0f));

    }

    void Scene::setupFloor()
    {

        // Create a plane
        Plane plane(Vector3::UNIT_Y, 0);

        // Define the plane mesh
        MeshManager::getSingleton().createPlane(
            "ground", RGN_DEFAULT,
            plane,
            1500, 1500, 20, 20,
            true,
            1, 5, 5,
            Vector3::UNIT_Z);

        // Create an entity for the ground
        Entity* groundEntity = scnMgr->createEntity("ground");

        // Setup ground entity
        //  Shadows off
        groundEntity->setCastShadows(false);

        // Material - Examples is the resources file,
        // Rockwall (texture/properties) is defined inside it.
        groundEntity->setMaterialName("Examples/Rockwall");

        // Create a scene node to add the mesh too.
        SceneNode* thisSceneNode = scnMgr->getRootSceneNode()->createChildSceneNode();
        thisSceneNode->attachObject(groundEntity);

        // the ground is a cube of side 100 at position y = 0.
        // the sphere will hit it at y = -6, with center at -5
        btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(750.), btScalar(50.), btScalar(750.)));

        collisionShapes.push_back(groundShape);

        btTransform groundTransform;
        groundTransform.setIdentity();

        Vector3 pos = thisSceneNode->_getDerivedPosition();

        // Box is 100 deep (dimensions are 1/2 heights)
        // but the plane position is flat.
        groundTransform.setOrigin(btVector3(pos.x, pos.y - 50.0, pos.z));

        Quaternion quat2 = thisSceneNode->_getDerivedOrientation();
        groundTransform.setRotation(btQuaternion(quat2.x, quat2.y, quat2.z, quat2.w));

        btScalar mass(0.);

        // rigidbody is dynamic if and only if mass is non zero, otherwise static
        bool isDynamic = (mass != 0.f);

        btVector3 localInertia(0, 0, 0);
        if (isDynamic)
            groundShape->calculateLocalInertia(mass, localInertia);

        // using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
        btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
        btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, groundShape, localInertia);
        btRigidBody* body = new btRigidBody(rbInfo);

        //   body->setRestitution(0.0);

        // add the body to the dynamics world
        dynamicsWorld->addRigidBody(body);
    }

    void Scene::setupLights()
    {
        // Setup Abient light
        scnMgr->setAmbientLight(ColourValue(0, 0, 0));
        scnMgr->setShadowTechnique(ShadowTechnique::SHADOWTYPE_STENCIL_MODULATIVE);

        // Add a spotlight
        Light* spotLight = scnMgr->createLight("SpotLight");

        // Configure
        spotLight->setDiffuseColour(0, 0, 1.0);
        spotLight->setSpecularColour(0, 0, 1.0);
        spotLight->setType(Light::LT_SPOTLIGHT);
        spotLight->setSpotlightRange(Degree(35), Degree(50));

        // Create a schene node for the spotlight
        SceneNode* spotLightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
        spotLightNode->setDirection(-1, -1, 0);
        spotLightNode->setPosition(Vector3(200, 200, 0));

        // Add spotlight to the scene node.
        spotLightNode->attachObject(spotLight);

        // Create directional light
        Light* directionalLight = scnMgr->createLight("DirectionalLight");

        // Configure the light
        directionalLight->setType(Light::LT_DIRECTIONAL);
        directionalLight->setDiffuseColour(ColourValue(0.4, 0, 0));
        directionalLight->setSpecularColour(ColourValue(0.4, 0, 0));

        // Setup a scene node for the directional lightnode.
        SceneNode* directionalLightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
        directionalLightNode->attachObject(directionalLight);
        directionalLightNode->setDirection(Vector3(0, -1, 1));

        // Create a point light
        Light* pointLight = scnMgr->createLight("PointLight");

        // Configure the light
        pointLight->setType(Light::LT_POINT);
        pointLight->setDiffuseColour(0.3, 0.3, 0.3);
        pointLight->setSpecularColour(0.3, 0.3, 0.3);

        // setup the scene node for the point light
        SceneNode* pointLightNode = scnMgr->getRootSceneNode()->createChildSceneNode();

        // Configure the light
        pointLightNode->setPosition(Vector3(0, 150, 250));

        // Add the light to the scene.
        pointLightNode->attachObject(pointLight);
    }

    void Scene::UseInputTest()
    {
        //if (XDGameEngine::Input::Instance().GetKeyDown("a"))
        //{
        //    for (auto& it = m_go.begin(); it != m_go.end(); ++it)
        //    {
        //        auto go = it->get();
        //        GameObject::Destroy(*go);
        //    }
        //}

        if (XDGameEngine::Input::Instance().GetKeyDown("a"))
        {
        }

        if (XDGameEngine::Input::Instance().GetKeyDown("f"))
        {
            for (auto& it = m_go.begin(); it != m_go.end(); ++it)
            {
                auto go = it->get();
                go->SetActive(!go->IsActive());
            }
        }
    }
}