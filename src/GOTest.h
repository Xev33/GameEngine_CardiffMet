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
            AddComponent(XDGameEngine::ComponentFactory::CreateComponent('INPT'));
            AddComponent(XDGameEngine::ComponentFactory::CreateComponent('MSRD'));
        }
        ~GOTest()
        {
            
        }

    };
}

#endif