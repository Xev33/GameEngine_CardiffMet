#ifndef ACOMPONENT_
#define ACOMPONENT_

#include <iostream>

namespace XDGameEngine
{
	class GameObject;
}

namespace XDGameEngine
{
	/**
	* Base abstract class that any new component must inherit from
	*/
	class AComponent
	{
	public:
		// Empty virtual destructor for an abstract class
		virtual ~AComponent() {}
	
		/**
		* Setup the entire component according to the current scene
		*/
		virtual void SetUpComponent() {};

		/**
		* The method that each GameObject will call each frame
		*/
		virtual void UpdateComponent(GameObject& go) {}

		/**
		* This method can be overriden in order to trigger behaviors (Eg: 
		* Register/unregister to dynamic world for the rigidbodie component)
		*/
		virtual void SetActive(bool isActive) {
			m_isActive = isActive;
			std::cout << "Component id " << m_id << " is now = " << m_isActive << std::endl;
		}
		bool IsActive() { return m_isActive; }
		uint32_t GetID() { return m_id; }
	
	private:

	protected:
		bool m_isActive = true;

		/**
		* The component ID is use as a reference for the component factory
		*/
		uint32_t m_id;
	};
}

#endif