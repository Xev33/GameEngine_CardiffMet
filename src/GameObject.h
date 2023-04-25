#ifndef GAMEOBJECT_
#define GAMEOBJECT_

#include <vector>
#include <memory>

/* Bullet3 Physics (for the transform)*/
#include "btBulletCollisionCommon.h"
#include "Transform.h"

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
		/**
		* The vector holding every gameobject's components
		*/
        std::vector<std::unique_ptr<XDGameEngine::AComponent>> m_components;
		bool m_isActive = true;
		bool m_shouldBeDestroyed = false;
		bool m_shouldBeUpdated = false;
		bool m_shouldBeScaled = true;


		Transform* m_transform;
    private:

    public:
        GameObject();
        ~GameObject();

		Transform* GetTransform() noexcept;

		/**
		* Method to get a component from the vector (gives nullptr if the component doesn't exist
		*/
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

		/**
		* Method to remove a component from the vector (call it destructor)
		*/
		template<typename T>
		void RemoveComponent()
		{
			bool hasBeenFound = false;

			for (auto it = m_components.begin(); it != m_components.end(); ++it) {
				if (dynamic_cast<T*>(it->get())) {
					m_components.erase(it);
					hasBeenFound = true;
					break;
				}
			}
			if (hasBeenFound == false)
				throw std::runtime_error("Non-existent component");
		}

		/**
		* Method to push a new component into the vector
		*/
        void AddComponent(std::unique_ptr<XDGameEngine::AComponent> component);

		/**
		* Method to toggle the gameobject's components activity on the scene
		*/
		void SetActive(bool isActive);
        bool IsActive() const noexcept;

		void Start();
		void Update();

		/**
		* Method to enable the boolean in order to tell to the scene to destroy the given gameobject
		*/
		static void Destroy(GameObject& go) noexcept;

		/**
		* this section is made for the scene to manage all the gameobjects lifetime
		*/
		void ActivateShouldDestroy() noexcept;
		bool ShouldBeDestroy() const noexcept;
		bool ShouldBeScaled() const noexcept;

		void ResetShouldBeScaled() noexcept;

		/**
		* Called by the scene each frame to apply what has been modify in the previous Update function
		*/
		void UpdateComponents() noexcept;
    };
}

#endif