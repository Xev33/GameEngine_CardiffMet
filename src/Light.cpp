#include "Light.h"
#include "Game.h"
#include "Scene.h"

namespace XDGameEngine
{
	//// LIGHT-----------------------------------------------------------
	Light::Light(const btVector3 pos, const btQuaternion rot, const btVector3 scale) :
		GameObject(pos, rot, scale)
	{
	}

	void Light::setType(Ogre::Light::LightTypes type) noexcept
	{
		m_light->setType(type);
	}

	Ogre::Light::LightTypes Light::getType() const noexcept
	{
		return m_light->getType();
	}

	Ogre::Light* Light::getLight() noexcept
	{
		return m_light;
	}

	//// ----------------------------------------------------------------
	//// ----------------------------------------------------------------
	//// ----------------------------------------------------------------
	//// ----------------------------------------------------------------
	//// ----------------------------------------------------------------
	//// ----------------------------------------------------------------
	//// ----------------------------------------------------------------

	//// POINT LIGHT ----------------------------------------------------
	PointLight::PointLight(const btVector3 pos) :
		Light(pos, btQuaternion(0.0f, 0.0f, 0.0f), btVector3(1.0f, 1.0f, 1.0f))
	{
		createLight();
	}

	void PointLight::createLight() noexcept
	{
		m_light = Game::Instance()->getCurrentScene()->getSceneManager()->createLight("PointLight");
		m_light->setType(Ogre::Light::LT_POINT);
		m_light->setDiffuseColour(0.6, 0.6, 0.6);
		m_light->setSpecularColour(0.3, 0.3, 0.3);

		m_lightNode = Game::Instance()->getCurrentScene()->getSceneManager()->getRootSceneNode()->createChildSceneNode();
		m_lightNode->setPosition(Ogre::Vector3(this->m_transform->getPosition().getX(), this->m_transform->getPosition().getY(), this->m_transform->getPosition().getZ()));
		m_lightNode->attachObject(m_light);
	}

	void PointLight::setDiffuseColour(float red, float green, float blue) noexcept
	{
		m_light->setDiffuseColour(red, green, blue);
	}

	void PointLight::setSpecularColour(float red, float green, float blue) noexcept
	{
		m_light->setSpecularColour(red, green, blue);
	}

	//// SPOT LIGHT ----------------------------------------------------
	SpotLight::SpotLight(const btVector3 pos, const btQuaternion rot) :
		Light(pos, rot, btVector3(1.0f, 1.0f, 1.0f))
	{
		createLight();
	}

	void SpotLight::createLight() noexcept
	{
		m_light = Game::Instance()->getCurrentScene()->getSceneManager()->createLight("SpotLight");
		m_light->setType(Ogre::Light::LT_SPOTLIGHT);
		m_light->setDiffuseColour(0, 0, 1.0);
		m_light->setSpecularColour(0, 0, 1.0);

		m_lightNode = Game::Instance()->getCurrentScene()->getSceneManager()->getRootSceneNode()->createChildSceneNode();
		m_lightNode->setPosition(Ogre::Vector3(this->m_transform->getPosition().getX(), this->m_transform->getPosition().getY(), this->m_transform->getPosition().getZ()));
		m_lightNode->setDirection(this->m_transform->getRotation().getX(), this->m_transform->getRotation().getY(), this->m_transform->getRotation().getZ());
		m_lightNode->attachObject(m_light);
	}

	void SpotLight::setDiffuseColour(float red, float green, float blue) noexcept
	{
		m_light->setDiffuseColour(red, green, blue);
	}

	void SpotLight::setSpecularColour(float red, float green, float blue) noexcept
	{
		m_light->setSpecularColour(red, green, blue);
	}

	void SpotLight::setSpotlightRange(const Ogre::Radian& innerAngle, const Ogre::Radian& outerAngle, Ogre::Real fallOff) noexcept
	{
		m_light->setSpotlightRange(innerAngle, outerAngle, fallOff);
	}

	//// DIRECTIONAL LIGHT ------------------------------------------------
	DirectionalLight::DirectionalLight(const btQuaternion rot) :
		Light(btVector3(1.0f, 1.0f, 1.0f), rot, btVector3(1.0f, 1.0f, 1.0f))
	{
		createLight();
	}

	void DirectionalLight::createLight() noexcept
	{
		m_light = Game::Instance()->getCurrentScene()->getSceneManager()->createLight("DirectionalLight");
		m_light->setType(Ogre::Light::LT_DIRECTIONAL);
		m_light->setDiffuseColour(Ogre::ColourValue(1,1,1));
		m_light->setSpecularColour(Ogre::ColourValue(1, 1, 1));

		m_lightNode = Game::Instance()->getCurrentScene()->getSceneManager()->getRootSceneNode()->createChildSceneNode();
		m_lightNode->setDirection(this->m_transform->getRotation().getX(), this->m_transform->getRotation().getY(), this->m_transform->getRotation().getZ());
		m_lightNode->attachObject(m_light);
	}

	void DirectionalLight::setDiffuseColour(const Ogre::ColourValue& colour) noexcept
	{
		m_light->setDiffuseColour(colour);
	}

	void DirectionalLight::setSpecularColour(const Ogre::ColourValue& colour) noexcept
	{
		m_light->setSpecularColour(colour);
	}

}