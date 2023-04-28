#include "XDPlayer.h"
#include "MeshRenderer.h"

namespace XDGameEngine
{
    XDPlayer::XDPlayer()
    {
        m_shouldBeUpdated = true;
        m_transform = nullptr;
        m_shouldBeDestroyed = false;
        AddComponent(XDGameEngine::ComponentFactory::CreateComponent('TRFM', *this));
        AddComponent(XDGameEngine::ComponentFactory::CreateComponent('MSRD', *this));
        AddComponent(XDGameEngine::ComponentFactory::CreateComponent('BXCS', *this));
        AddComponent(XDGameEngine::ComponentFactory::CreateComponent('RGBD', *this));
        this->GetComponent<MeshRenderer>()->SetMeshFileName("cube.mesh");
        this->m_transform = this->GetComponent<Transform>();

        m_transform->setScale(btVector3(1, 1.5f, 1));
        this->m_transform->setPosition(btVector3(-200, 100, 3));
        this->m_transform->setRotation(btQuaternion(0, 45, 3));
        SetupAllComponents();
    }

    XDPlayer::~XDPlayer()
    {

    }
}