#include "Cube.h"

#include "MeshRenderer.h"
#include "Rigibodies.h"

#include "Input.h"
#include "Game.h"
#include "Scene.h"
#include "TriggerZone.h"

#define _USE_MATH_DEFINES
#include <math.h>

namespace XDGameEngine
{
    Cube::Cube(const btVector3 pos, const btQuaternion rot, const btVector3 scale) :
        GameObject(pos, rot, scale)
    {
        AddComponent(XDGameEngine::ComponentFactory::CreateComponent('MSRD', *this));
        AddComponent(XDGameEngine::ComponentFactory::CreateComponent('BXCS', *this));
        AddComponent(XDGameEngine::ComponentFactory::CreateComponent('RGBD', *this));
        this->GetComponent<MeshRenderer>()->SetMeshFileName("cube.mesh");
        body = this->GetComponent<RigidBody>();
        body->SetMass(0.0f);
        SetupAllComponents();
        GetComponent<MeshRenderer>()->GetMesh()->setMaterialName("Examples/Rockwall");
        m_rgbd = body->GetRigidbody();
    }

    Cube::~Cube()
    {
        m_shouldBeUpdated = true;
        m_transform = nullptr;
        m_rgbd = nullptr;
    }

}