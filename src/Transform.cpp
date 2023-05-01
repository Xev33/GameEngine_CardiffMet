#include "Transform.h"

namespace XDGameEngine
{
	//Transform::Transform()
	//{
	//	m_id = 'TRFM';
	//	// Initialize the transform to an identity matrix
	//	m_rotation = btQuaternion(0, 0, 0, 1);
	//	m_position.setZero();
	//}

    Transform::Transform(const btVector3 pos, const btQuaternion rot, const btVector3 scale)
    {
        m_id = 'TRFM';
        // Initialize the transform to an identity matrix
        m_position = pos;
        m_rotation = rot;
        m_scale = scale;
    }

	Transform::Transform(const btTransform& transform)
	{
		m_id = 'TRFM';
		// Copy the rotation and translation from the btTransform
		m_rotation = transform.getRotation();
		m_position = transform.getOrigin();
	}

	Transform::~Transform()
	{
	}

    btTransform Transform::toBulletTransform() const
    {
        btTransform transform;
        transform.setRotation(m_rotation);
        transform.setOrigin(m_position);
        return transform;
    }

    // Setters
    void Transform::setRotation(const btQuaternion& rotation)
    {
        m_rotation = rotation;
    }

    void Transform::setPosition(const btVector3& translation)
    {
        m_position = translation;
    }

    void Transform::setScale(const btVector3& scale)
    {
        m_scale = scale;
    }

    // Getters
    btQuaternion Transform::getRotation() const
    {
        return m_rotation;
    }

    btVector3 Transform::getPosition() const
    {
        return m_position;
    }

    btVector3 Transform::getScale() const
    {
        return m_scale;
    }

	void Transform::printUnAutreTruc()
	{
		std::cout << "TRANSFORM PRINT UN TRUC\n";
	}

}