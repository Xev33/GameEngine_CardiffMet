#include "Scene.h"
#include "Input.h"

#include "Player.h"
#include "Light.h"
#include "NPC.h"
#include "TriggerZone.h"
#include "Rigibodies.h"
#include "Transform.h"
#include <iostream>

#include "Cube.h"
#include "CollisionShape.h"
#include "MeshRenderer.h"
#include "OgreBullet.h"

#include <memory>
#include "BulletCollision/CollisionDispatch/btGhostObject.h"

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

            // Update all game objects who need to be updated
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
                }
                    ++it;
            }

            dynamicsWorld->stepSimulation((float)evt.timeSinceLastFrame, 10);


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





        setupCamera();

        setupMovingObj();

        setupStaticObj();
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

        // We setup the world to accept ghost object in order to have trigger zone
        // Found here: https://gamedev.net/forums/topic/692573-bullet-btghostobject/5358842/
        dynamicsWorld->getPairCache()->setInternalGhostPairCallback(new btGhostPairCallback());
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
        //camNode->attachObject(cam);
        m_go.at(0)->GetComponent<MeshRenderer>()->GetSceneNode()->attachObject(cam);

        // Setup viewport for the camera.
        // I SHOULD PROBABLY MOVE THE VIEWPORT TO THE GAME CLASS
        Ogre::Viewport* vp = rw->addViewport(cam);
        vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));

        // link the camera and view port.
        cam->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
    }

    void Scene::setupMovingObj() noexcept
    {
        /*
        * It is easy to use an XML doc parser to put all these datas in
        * It should use a GameObject factory
        * Unfortunately I am running out of time
        */
        m_go.push_back(std::make_unique<Player>(
            btVector3(0.0f, 80.0f, 200.0f),
            btQuaternion(0, 0, 0),
            btVector3(1.0f, 2.0f, 1.0f)));
        //npc1
        auto& npc1 = std::make_unique<NPC>(
            btVector3(500.0f, 80.0f, -1000.0f),
            btQuaternion(0, 0, 0),
            btVector3(1.0f, 1.0f, 1.0f));
        npc1->AddWayPoint(btVector3(-500.0f, 80.0f, -1000.0f));
        m_go.push_back(std::move(npc1));
        //npc2
        auto& npc2 = std::make_unique<NPC>(
            btVector3(-500.0f, 80.0f, -800.0f),
            btQuaternion(0, 0, 0),
            btVector3(1.0f, 1.0f, 1.0f));
        npc2->AddWayPoint(btVector3(500.0f, 80.0f, -800.0f));
        m_go.push_back(std::move(npc2));
        //npc3
        auto& npc3 = std::make_unique<NPC>(
            btVector3(-3300.0f, 680.0f, -3500.0f),
            btQuaternion(0, 0, 0),
            btVector3(1.0f, 1.0f, 1.0f));
        npc3->AddWayPoint(btVector3(-3300.0f, 680.0f, -2500.0f));
        npc3->AddWayPoint(btVector3(-2800.0f, 680.0f, -2500.0f));
        npc3->AddWayPoint(btVector3(-2800.0f, 680.0f, -3500.0f));
        m_go.push_back(std::move(npc3));
        //npc4
        auto& npc4 = std::make_unique<NPC>(
            btVector3(-2800.0f, 680.0f, -2500.0f),
            btQuaternion(0, 0, 0),
            btVector3(1.0f, 1.0f, 1.0f));
        npc4->AddWayPoint(btVector3(-2800.0f, 680.0f, -3500.0f));
        npc4->AddWayPoint(btVector3(-3300.0f, 680.0f, -3500.0f));
        npc4->AddWayPoint(btVector3(-3300.0f, 680.0f, -2500.0f));
        m_go.push_back(std::move(npc4));
    }

    void Scene::setupStaticObj() noexcept
    {
        /*
        * As the moving object: It should use an XML doc, parse it
        * Create each gameObject with a GameObject factory
        * Unfortunately I am running out of time
        */
        //Ground
        m_go.push_back(std::make_unique<Cube>(
            btVector3(0.0f, 1.0f, 0.0f),
            btQuaternion(0, 0, 0),
            btVector3(15.0f, 0.5f, 15.0f)));
        //Ground2
        m_go.push_back(std::make_unique<Cube>(
            btVector3(0.0f, 1.0f, -1500.0f),
            btQuaternion(0, 0, 0),
            btVector3(15.0f, 0.5f, 15.0f)));
        //Ground3
        m_go.push_back(std::make_unique<Cube>(
            btVector3(0.0f, 200.0f, -3000.0f),
            btQuaternion(0, 0, 0),
            btVector3(15.0f, 4.0f, 15.0f)));
        //Ground4
        m_go.push_back(std::make_unique<Cube>(
            btVector3(-2500.0f, 1.0f, -3000.0f),
            btQuaternion(0, 0, 0),
            btVector3(35.0f, 0.5f, 15.0f)));
        //Ground5
        m_go.push_back(std::make_unique<Cube>(
            btVector3(-5000.0f, 200.0f, -3000.0f),
            btQuaternion(0, 0, 0),
            btVector3(15.0f, 4.0f, 15.0f)));
        //Ground6
        m_go.push_back(std::make_unique<Cube>(
            btVector3(-3000.0f, 600.0f, -3000.0f),
            btQuaternion(0, 0, 45),
            btVector3(10.0f, 0.5f, 15.0f)));


        //Roof
        m_go.push_back(std::make_unique<Cube>(
            btVector3(0.0f, 800.0f, 0.0f),
            btQuaternion(0, 0, 0),
            btVector3(15.0f, 0.5f, 15.0f)));
        //Roof2
        m_go.push_back(std::make_unique<Cube>(
            btVector3(0.0f, 800.0f, -1500.0f),
            btQuaternion(0, 0, 0),
            btVector3(15.0f, 0.5f, 15.0f)));
        //Roof3
        m_go.push_back(std::make_unique<Cube>(
            btVector3(0.0f, 800.0f, -3000.0f),
            btQuaternion(0, 0, 0),
            btVector3(15.0f, 0.5f, 15.0f)));
        //Roof4
        m_go.push_back(std::make_unique<Cube>(
            btVector3(-2500.0f, 1200.0f, -3000.0f),
            btQuaternion(0, 0, 0),
            btVector3(35.0f, 0.5f, 15.0f)));
        //Roof5
        m_go.push_back(std::make_unique<Cube>(
            btVector3(-5000.0f, 1200.0f, -3000.0f),
            btQuaternion(0, 0, 0),
            btVector3(15.0f, 0.5f, 15.0f)));


        //left
        m_go.push_back(std::make_unique<Cube>(
            btVector3(750.0f, 400.0f, -750.0f),
            btQuaternion(0, 0, 0),
            btVector3(0.5f, 8.0f, 30.0f)));
        //left2
        m_go.push_back(std::make_unique<Cube>(
            btVector3(750.0f, 400.0f, -3000.0f),
            btQuaternion(0, 0, 0),
            btVector3(0.5f, 8.0f, 15.0f)));
        //left3
        m_go.push_back(std::make_unique<Cube>(
            btVector3(-5750.0f, 600.0f, -3000.0f),
            btQuaternion(0, 0, 0),
            btVector3(0.5f, 12.0f, 15.0f)));


        //right
        m_go.push_back(std::make_unique<Cube>(
            btVector3(-750.0f, 400.0f, -750.0f),
            btQuaternion(0, 0, 0),
            btVector3(0.5f, 8.0f, 30.0f)));


        //back
        m_go.push_back(std::make_unique<Cube>(
            btVector3(0.0f, 400.0f, 750.0f),
            btQuaternion(0, 0, 0),
            btVector3(15.f, 8.0f, 0.5f)));
        //back2
        m_go.push_back(std::make_unique<Cube>(
            btVector3(0.0f, 400.0f, -3750.0f),
            btQuaternion(0, 0, 0),
            btVector3(15.f, 8.0f, 0.5f)));
        //back3
        m_go.push_back(std::make_unique<Cube>(
            btVector3(-3250.0f, 600.0f, -3750.0f),
            btQuaternion(0, 0, 0),
            btVector3(50.f, 12.0f, 0.5f)));

        //back3
        m_go.push_back(std::make_unique<Cube>(
            btVector3(-3250.0f, 600.0f, -2250.0f),
            btQuaternion(0, 0, 0),
            btVector3(50.f, 12.0f, 0.5f)));


        //Lights setup
        m_go.push_back(std::make_unique<PointLight>(btVector3(0, 250, 250)));

        m_go.push_back(std::make_unique<DirectionalLight>(btQuaternion(1, 45, 1)));

        m_go.push_back(std::make_unique<SpotLight>(
            btVector3(1000, 1000, -3000),
            btQuaternion(45, 1, 0)));
    }

    void Scene::UseInputTest()
    {
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

//https://gamedev.net/forums/topic/692573-bullet-btghostobject/5358842/
//if (m_Ghostobject == nullptr)
//    return;
//for (int i = 0, end = m_Ghostobject->getNumOverlappingObjects(); i != end; ++i)
//{
//    btCollisionObject* c = m_Ghostobject->getOverlappingObject(i);
//    MyContactResultCallback results;
//    dynamicsWorld->contactPairTest(m_Ghostobject, c, results);
//    if (results.hitObject)
//    {
//        uint32_t* tag = static_cast<uint32_t*>(c->getUserPointer());;
//        uint32_t kek = 'PLYR';
//        std::cout << *tag << " ENFIN!!! " << kek << "\n";
//        dynamicsWorld->removeCollisionObject(m_Ghostobject);
//        delete m_Ghostobject;
//        m_Ghostobject = nullptr;
//        return;
//    }
//}

    //void Scene::setupFloor()
    //{

    //    // Create a plane
    //    Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);

    //    // Define the plane mesh
    //    Ogre::MeshManager::getSingleton().createPlane(
    //        "ground", Ogre::RGN_DEFAULT,
    //        plane,
    //        1500, 1500, 20, 20,
    //        true,
    //        1, 5, 5,
    //        Ogre::Vector3::UNIT_Z);

    //    // Create an entity for the ground
    //    Ogre::Entity* groundEntity = scnMgr->createEntity("ground");

    //    // Setup ground entity
    //    //  Shadows off
    //    groundEntity->setCastShadows(false);

    //    // Material - Examples is the resources file,
    //    // Rockwall (texture/properties) is defined inside it.
    //    groundEntity->setMaterialName("Examples/Rockwall");

    //    // Create a scene node to add the mesh too.
    //    Ogre::SceneNode* thisSceneNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    //    thisSceneNode->attachObject(groundEntity);

    //    // the ground is a cube of side 100 at position y = 0.
    //    // the sphere will hit it at y = -6, with center at -5
    //    btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(750.), btScalar(50.), btScalar(750.)));

    //    collisionShapes.push_back(groundShape);

    //    btTransform groundTransform;
    //    groundTransform.setIdentity();

    //    Ogre::Vector3 pos = thisSceneNode->_getDerivedPosition();

    //    // Box is 100 deep (dimensions are 1/2 heights)
    //    // but the plane position is flat.
    //    groundTransform.setOrigin(btVector3(pos.x, pos.y - 50.0, pos.z));

    //    Ogre::Quaternion quat2 = thisSceneNode->_getDerivedOrientation();
    //    groundTransform.setRotation(btQuaternion(quat2.x, quat2.y, quat2.z, quat2.w));

    //    btScalar mass(0.);

    //    // rigidbody is dynamic if and only if mass is non zero, otherwise static
    //    bool isDynamic = (mass != 0.f);

    //    btVector3 localInertia(0, 0, 0);
    //    if (isDynamic)
    //        groundShape->calculateLocalInertia(mass, localInertia);

    //    // using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
    //    btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
    //    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, groundShape, localInertia);
    //    btRigidBody* body = new btRigidBody(rbInfo);

    //    //   body->setRestitution(0.0);

    //    // add the body to the dynamics world
    //    dynamicsWorld->addRigidBody(body);
    //}