#include "XDPlayer.h"
#include "MeshRenderer.h"

namespace XDGameEngine
{
    XDPlayer::XDPlayer()
    {
        m_shouldBeUpdated = true;
        m_transform = nullptr;
        AddComponent(XDGameEngine::ComponentFactory::CreateComponent('TRFM', *this));
        AddComponent(XDGameEngine::ComponentFactory::CreateComponent('RGBD', *this));
        AddComponent(XDGameEngine::ComponentFactory::CreateComponent('MSRD', *this));
        this->GetComponent<MeshRenderer>()->SetMeshFileName("cube.mesh");
        this->GetComponent<MeshRenderer>()->SetUpComponent();
        this->m_transform = this->GetComponent<Transform>();
        m_transform->setScale(btVector3(1, 4, 1));
    }

    XDPlayer::~XDPlayer()
    {

    }
}