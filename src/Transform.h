#ifndef TRANSFROM_
#define TRANSFROM_

/* Bullet3 Physics (for the transform)*/
#include "btBulletCollisionCommon.h"

#include "AComponent.h"

namespace XDGameEngine
{
    class Transform : public AComponent {
    public:
        Transform();
        Transform(const btTransform& transform);

        ~Transform();

        btTransform toBulletTransform() const;

        // Setters
        void setRotation(const btQuaternion& rotation);
        void setPosition(const btVector3& translation);
        void setScale(const btVector3& scale);

        // Getters
        btQuaternion getRotation() const;
        btVector3 getPosition() const;
        btVector3 getScale() const;

        void printUnAutreTruc();

    private:
        btQuaternion m_rotation;
        btVector3 m_position;
        btVector3 m_scale;
    };
}

#endif