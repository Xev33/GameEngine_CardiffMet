#ifndef GAMEOBJECT_
#define GAMEOBJECT_

#include <vector>
#include <memory>

/* Forward declaration for the Input */
namespace XDGameEngine
{
    class AComponent;
}

namespace XDGameEngine
{
    class GameObject
    {
    protected:
        std::vector<std::unique_ptr<XDGameEngine::AComponent>> m_components;
        bool m_isActive;

    private:

    public:
        GameObject();
        ~GameObject();

		template<typename T>
		T* GetComponent()
		{
			static_assert(std::is_base_of<XDGameEngine::AComponent, T>::value, "T must be a subclass of Component");

			for (auto& component : m_components) {
				T* tComponent = dynamic_cast<T*>(component.get());
				if (tComponent != nullptr) {
					return tComponent;
				}
			}

			return nullptr;
		}

		template<typename T>
		void RemoveComponent()
		{
			bool hasBeenFound = false;

			for (auto it = m_components.begin(); it != m_components.end(); ++it) {
				if (dynamic_cast<T*>(it->get())) {
					//auto tmp = std::move(it);
					m_components.erase(it);
					//delete tmp;
					hasBeenFound = true;
					break;
				}
			}
			if (hasBeenFound == false)
				throw std::runtime_error("Non-existent component");
		}

        void AddComponent(std::unique_ptr<XDGameEngine::AComponent> component);

        void SetActive(bool isActive);
        bool IsActive() const noexcept;
    };
}

#endif