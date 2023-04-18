#ifndef ACOMPONENT_
#define ACOMPONENT_

#include <iostream>

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
	
		void SetActive(bool isActive) {
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