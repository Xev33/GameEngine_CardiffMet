#include "GameObject.h"
#include "AComponent.h"
#include <type_traits> // CHECKER IF IT IS MANDATORY OR NOT

namespace XDGameEngine
{
	GameObject::GameObject()
	{
		m_isActive = true;
	}

	GameObject::~GameObject()
	{
		std::cout << m_components.size() << " la taille\n";
	}

	void GameObject::AddComponent(std::unique_ptr<XDGameEngine::AComponent> component)
	{
		for (int i = 0; i < m_components.size(); ++i) {
			if (component->GetID() == m_components.at(i)->GetID())
			{
				throw std::runtime_error("You are trying to add an already existing component");
			}
		}
		m_components.push_back(std::move(component));
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

	bool GameObject::IsActive() const noexcept
	{
		return m_isActive;
	}
}