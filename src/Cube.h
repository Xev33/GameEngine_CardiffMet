#ifndef CUBE_
#define CUBE_

#include "GameObject.h"
#include "ComponentFactory.h"
#include "AComponent.h"
#include "Rigibodies.h"

namespace XDGameEngine
{
    class Cube : public GameObject
    {
    protected:

    private:

        btRigidBody* m_rgbd;
        RigidBody* body;

    public:
        Cube(const btVector3 pos = btVector3(1.0f, 1.0f, 1.0f),
            const btQuaternion rot = btQuaternion(0.0f, 0.0f, 0.0f),
            const btVector3 scale = btVector3(1.0f, 1.0f, 1.0f));
        ~Cube();
    };
}

#endif