#ifndef ACOMPONENT_
#define ACOMPONENT_

namespace XDGameEngine
{
	class AComponent
	{
	public:
		// Empty virtual destructor for proper cleanup
		virtual ~AComponent() {}
	
		virtual void SetActive(bool isActive) = 0;
		AComponent& GetComponent() { return *this; }
	
	private:
		bool m_isActive;
	};
}

#endif