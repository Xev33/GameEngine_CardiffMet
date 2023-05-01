#ifndef COLLISION_SHAPE
#define COLLISION_SHAPE

#include "GameObject.h"

#include "OgreRTShaderSystem.h"
#include "OgreCameraMan.h"
#include "Ogre.h"

namespace XDGameEngine
{
	/**
	* Base abstract class that any shape will inherit from
	*/
	class Light : public GameObject
	{
	protected:
		/*
		* The light's pointer
		*/
		Ogre::Light* m_light;

		/*
		* The light's node
		*/
		Ogre::SceneNode* m_lightNode;

	private:

	public:
		Light(const btVector3 pos = btVector3(1.0f, 1.0f, 1.0f),
			const btQuaternion rot = btQuaternion(0.0f, 0.0f, 0.0f),
			const btVector3 scale = btVector3(1.0f, 1.0f, 1.0f));
		~Light() {}
	
		/*
		* Create the light and it node
		*/
		virtual void createLight() noexcept {}

		/*
		* Modify the light pointer's diffuse
		*/
		virtual void setDiffuseColour(float red, float green, float blue) noexcept {}

		/*
		* Modify the light pointer's Specular
		*/
		virtual void setSpecularColour(float red, float green, float blue) noexcept {}


		/*
		* Set the light's type
		*/
		virtual void setType(Ogre::Light::LightTypes type) noexcept;

		/*
		* Get the light's type
		*/
		virtual Ogre::Light::LightTypes getType() const noexcept;

		/*
		* Get the light's adress
		*/
		virtual Ogre::Light* getLight() noexcept;


	};

	class PointLight : public Light
	{
	private:
	public:
		PointLight(const btVector3 pos = btVector3(1.0f, 1.0f, 1.0f));
		~PointLight() {}
		virtual void createLight() noexcept final;
		virtual void setDiffuseColour(float red, float green, float blue) noexcept final;
		virtual void setSpecularColour(float red, float green, float blue) noexcept final;
	};

	class SpotLight : public Light
	{
	private:
	public:
		SpotLight(const btVector3 pos = btVector3(1.0f, 1.0f, 1.0f),
			const btQuaternion rot = btQuaternion(0.0f, 0.0f, 0.0f));
		~SpotLight() {}
		virtual void createLight() noexcept final;
		virtual void setDiffuseColour(float red, float green, float blue) noexcept final;
		virtual void setSpecularColour(float red, float green, float blue) noexcept final;
		void setSpotlightRange(const Ogre::Radian& innerAngle, const Ogre::Radian& outerAngle, Ogre::Real fallOff = 1.0F) noexcept;
	};

	class DirectionalLight : public Light
	{
	private:
	public:
		DirectionalLight(const btQuaternion rot = btQuaternion(0.0f, 0.0f, 0.0f));
		~DirectionalLight() {}
		virtual void createLight() noexcept final;
		virtual void setDiffuseColour(const Ogre::ColourValue& colour) noexcept final;
		virtual void setSpecularColour(const Ogre::ColourValue& colour) noexcept final;
	};
}

#endif