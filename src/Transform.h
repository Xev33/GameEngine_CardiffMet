#ifndef TRANSFROM_
#define TRANSFROM_

/* Bullet3 Physics (for the transform)*/
#include "btBulletCollisionCommon.h"

#include "AComponent.h"

namespace XDGameEngine
{
    /**
    * This Transform class is an abstraction of the btTransform class.
    * It is a component class for the game engine using the btVector and btQuaternion classes
    * It can be used with the bullet classes and Ogre classes
    */
    class Transform : public AComponent {
    public:
        //Transform();
        Transform(const btVector3 pos = btVector3(1.0f, 1.0f, 1.0f),
            const btQuaternion rot = btQuaternion(0.0f, 0.0f, 0.0f),
            const btVector3 scale = btVector3(1.0f, 1.0f, 1.0f));

        /**
        * Copy-constructor for a btTransform
        */
        Transform(const btTransform& transform);

        ~Transform();

        /**
        * Methode to convert this transform to a btTransform for the api to use our data
        */
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