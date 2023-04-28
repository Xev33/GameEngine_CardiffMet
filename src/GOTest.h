#ifndef GO_TEST_
#define GO_TEST_

#include "GameObject.h"
#include "ComponentFactory.h"
#include "AComponent.h"

namespace XDGameEngine
{
    class GOTest : public XDGameEngine::GameObject
    {
    protected:

    private:

    public:
        GOTest()
        {
            m_transform = nullptr;
            m_shouldBeUpdated = true;
            AddComponent(XDGameEngine::ComponentFactory::CreateComponent('TRFM', *this));
            //AddComponent(XDGameEngine::ComponentFactory::CreateComponent('RGBD', *this) );
            //AddComponent(XDGameEngine::ComponentFactory::CreateComponent('MSRD', *this) );
            m_transform = GetComponent<Transform>();
        }
        ~GOTest()
        {
            
        }

    };
}

#endif