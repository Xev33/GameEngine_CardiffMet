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

		/**
		* Boolean to notify the scene if it should be updated
		*/
		bool m_isActive = true;

		/**
		* Boolean to notify the scene if it should be destroyed
		*/
		bool m_shouldBeDestroyed = false;

		/**
		* Boolean allowing the current scene to know if it should go into 
		* the GameObjectToUpdate list
		*/
		bool m_shouldBeUpdated = false;

		/**
		* Boolean to notify the potential mesh renderer if it should update the scale
		*/
		bool m_shouldBeScaled = true;

		/**
		* The only component that EVERY gameObject have
		*/
		Transform* m_transform;

		/**
		* the game object's name
		*/
		std::string m_name;

		/**
		* Tag will come later. Very low priority
		*/
		const char* m_tag;

    private:// no private member -> Should I remove it?

    public:
		GameObject(const btVector3 pos, const btQuaternion rot, const btVector3 scale);
        ~GameObject();

		const char* getTag()
		{
			return m_tag;
		}
		/**
		* Getter for the gameObject's inner transform
		*/
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
		* Trigger the SetupComponent for each component in the m_components vector
		*/
		void SetupAllComponents() noexcept;

		/**
		* Method to toggle the gameobject's components activity on the scene
		*/
		void SetActive(bool isActive);

		/**
		* Method to know if the gameobject should be update by the scene
		*/
        bool IsActive() const noexcept;

		/**
		* Is called when created
		*/
		virtual void Start();

		/**
		* Is called each frame by the scene
		*/
		virtual void Update();

		/**
		* Method to enable the boolean in order to tell to the scene to destroy the given gameobject
		*/
		static void Destroy(GameObject& go) noexcept;

		/**
		* this section is made for the scene to manage all the gameobjects lifetime
		*/
		void ActivateShouldDestroy() noexcept;

		/**
		* Notify the scene if it must be remove from its vector (trigger the Dtor)
		*/
		bool ShouldBeDestroy() const noexcept;

		/**
		* Notify the potential mesh renderer if it must be rescaled
		* (There is surely a better way but I am running out of time)
		*/
		bool ShouldBeScaled() const noexcept;

		/**
		* Stop the potentiel mesh renderer to rescale the mesh
		* (There is surely a better way but I am running out of time)
		*/
		void ResetShouldBeScaled() noexcept;

		/**
		* Called by the scene each frame to apply what has been modify in the previous Update function
		*/
		void UpdateComponents() noexcept;
    };
}

#endif