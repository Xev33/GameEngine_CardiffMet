#include "GameObject.h"
#include "AComponent.h"

namespace XDGameEngine
{
	GameObject::GameObject()
	{
	}

	GameObject::~GameObject()
	{
		std::cout << m_components.size() << " la taille\n"; // To remove when the project is done
	}

	void GameObject::AddComponent(std::unique_ptr<XDGameEngine::AComponent> component)
	{
		for (int i = 0; i < m_components.size(); ++i)
		{
			// We check if the gameObject already has this component
			if (component->GetID() == m_components.at(i)->GetID())
			{
				throw std::runtime_error("You are trying to add an already existing component");
			}
		}
		// We ude std::move in order to give the ownership to the gameobject
		m_components.push_back(std::move(component));
	}

	void GameObject::SetupAllComponents() noexcept
	{
		for (int i = 0; i < m_components.size(); ++i)
		{
			m_components.at(i)->SetUpComponent(*this);
		}
	}

	void GameObject::Start()
	{
	}

	void GameObject::Update()
	{
	}

	void GameObject::Destroy(GameObject& go) noexcept
	{
		go.ActivateShouldDestroy();
	}

	void GameObject::SetActive(bool isActive)
	{
		m_isActive = isActive;

		for (int i = 0; i < m_components.size(); ++i)
		{
			if (m_components.at(i)->IsActive() != m_isActive)
				m_components.at(i)->SetActive(m_isActive);
		}
	}

	Transform* GameObject::GetTransform() noexcept
	{
		return m_transform;
	}

	void GameObject::ActivateShouldDestroy() noexcept
	{
		m_shouldBeDestroyed = true;
	}

	bool GameObject::ShouldBeDestroy() const noexcept
	{
		return m_shouldBeDestroyed;
	}

	bool GameObject::ShouldBeScaled() const noexcept
	{
		return m_shouldBeScaled;
	}

	void GameObject::ResetShouldBeScaled() noexcept
	{
		m_shouldBeScaled = false;
	}

	bool GameObject::IsActive() const noexcept
	{
		return m_isActive;
	}

	void GameObject::UpdateComponents() noexcept
	{
		for (auto& component : m_components)
		{
			if (component->IsActive() == true)
				component->UpdateComponent(*this);
		}
	}


}