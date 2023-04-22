#ifndef TRANSFROM_
#define TRANSFROM_

/* Bullet3 Physics (for the transform)*/
#include "btBulletCollisionCommon.h"

#include "AComponent.h"

namespace XDGameEngine
{
	class Transform : public XDGameEngine::AComponent, public btTransform
	{
	private:

	protected:

		///Storage for the rotation
		btMatrix3x3 m_basis;
		///Storage for the translation
		btVector3 m_origin;
	public:
		Transform();
		~Transform();

		void printUnAutreTruc();

		Transform& operator=(const btTransform& other)
		{
			m_basis = other.getBasis();
			m_origin = other.getOrigin();
			return *this;
		}
		
		explicit SIMD_FORCE_INLINE Transform(const btQuaternion& q,
			const btVector3& c = btVector3(btScalar(0), btScalar(0), btScalar(0)))
			: m_basis(q),
			m_origin(c)
		{
		}

		/**@brief Constructor from btMatrix3x3 (optional btVector3)
	   * @param b Rotation from Matrix
	   * @param c Translation from Vector default (0,0,0)*/
		explicit SIMD_FORCE_INLINE Transform(const btMatrix3x3& b,
			const btVector3& c = btVector3(btScalar(0), btScalar(0), btScalar(0)))
			: m_basis(b),
			m_origin(c)
		{
		}
		/**@brief Copy constructor */
		SIMD_FORCE_INLINE Transform(const btTransform& other)
			: m_basis(other.getBasis()),
			m_origin(other.getOrigin())
		{
		}

		/**@brief Set the current transform as the value of the product of two transforms
	   * @param t1 Transform 1
	   * @param t2 Transform 2
	   * This = Transform1 * Transform2 */
		SIMD_FORCE_INLINE void mult(const btTransform& t1, const btTransform& t2)
		{
			m_basis = t1.getBasis() * t2.getBasis();
			m_origin = t1(t2.getOrigin());
		}

		/*		void multInverseLeft(const btTransform& t1, const btTransform& t2) {
				btVector3 v = t2.m_origin - t1.m_origin;
				m_basis = btMultTransposeLeft(t1.m_basis, t2.m_basis);
				m_origin = v * t1.m_basis;
			}
			*/

			/**@brief Return the transform of the vector */
		SIMD_FORCE_INLINE btVector3 operator()(const btVector3& x) const
		{
			return x.dot3(m_basis[0], m_basis[1], m_basis[2]) + m_origin;
		}

		/**@brief Return the transform of the vector */
		SIMD_FORCE_INLINE btVector3 operator*(const btVector3& x) const
		{
			return (*this)(x);
		}

		/**@brief Return the transform of the btQuaternion */
		SIMD_FORCE_INLINE btQuaternion operator*(const btQuaternion& q) const
		{
			return getRotation() * q;
		}

		/**@brief Return the basis matrix for the rotation */
		SIMD_FORCE_INLINE btMatrix3x3& getBasis() { return m_basis; }
		/**@brief Return the basis matrix for the rotation */
		SIMD_FORCE_INLINE const btMatrix3x3& getBasis() const { return m_basis; }

		/**@brief Return the origin vector translation */
		SIMD_FORCE_INLINE btVector3& getOrigin() { return m_origin; }
		/**@brief Return the origin vector translation */
		SIMD_FORCE_INLINE const btVector3& getOrigin() const { return m_origin; }

		/**@brief Return a quaternion representing the rotation */
		btQuaternion getRotation() const
		{
			btQuaternion q;
			m_basis.getRotation(q);
			return q;
		}

		/**@brief Set from an array
	   * @param m A pointer to a 16 element array (12 rotation(row major padded on the right by 1), and 3 translation */
		void setFromOpenGLMatrix(const btScalar* m)
		{
			m_basis.setFromOpenGLSubMatrix(m);
			m_origin.setValue(m[12], m[13], m[14]);
		}

		/**@brief Fill an array representation
	   * @param m A pointer to a 16 element array (12 rotation(row major padded on the right by 1), and 3 translation */
		void getOpenGLMatrix(btScalar* m) const
		{
			m_basis.getOpenGLSubMatrix(m);
			m[12] = m_origin.x();
			m[13] = m_origin.y();
			m[14] = m_origin.z();
			m[15] = btScalar(1.0);
		}

		/**@brief Set the translational element
	   * @param origin The vector to set the translation to */
		SIMD_FORCE_INLINE void setOrigin(const btVector3& origin)
		{
			m_origin = origin;
		}

		/**@brief Set the rotational element by btMatrix3x3 */
		SIMD_FORCE_INLINE void setBasis(const btMatrix3x3& basis)
		{
			m_basis = basis;
		}

		/**@brief Set the rotational element by btQuaternion */
		SIMD_FORCE_INLINE void setRotation(const btQuaternion& q)
		{
			m_basis.setRotation(q);
		}

		/**@brief Set this transformation to the identity */
		void setIdentity()
		{
			m_basis.setIdentity();
			m_origin.setValue(btScalar(0.0), btScalar(0.0), btScalar(0.0));
		}

		/**@brief Multiply this Transform by another(this = this * another)
	   * @param t The other transform */
		Transform& operator*=(const btTransform& t)
		{
			m_origin += m_basis * t.getOrigin();
			m_basis *= t.getBasis();
			return *this;
		}

		/**@brief Return the inverse of this transform */
		Transform inverse() const
		{
			btMatrix3x3 inv = m_basis.transpose();
			return btTransform(inv, inv * -m_origin);
		}

		/**@brief Return the inverse of this transform times the other transform
	   * @param t The other transform
	   * return this.inverse() * the other */

		/**@brief Return an identity transform */
		static const Transform& getIdentity()
		{
			static const btTransform identityTransform(btMatrix3x3::getIdentity());
			return identityTransform;
		}
	};
}

#endif