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
        GOTest(const btVector3 pos = btVector3(1.0f, 1.0f, 1.0f),
            const btQuaternion rot = btQuaternion(0.0f, 0.0f, 0.0f),
            const btVector3 scale = btVector3(1.0f, 1.0f, 1.0f)) :
            GameObject(pos, rot, scale)
        {
        }
        ~GOTest()
        {
            
        }

    };
}

#endif