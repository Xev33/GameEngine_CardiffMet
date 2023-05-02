#include "GameObject.h"
#include "AComponent.h"
#include "ComponentFactory.h"

namespace XDGameEngine
{
	GameObject::GameObject(const btVector3 pos = btVector3(1.0f, 1.0f, 1.0f),
		const btQuaternion rot = btQuaternion(0.0f, 0.0f, 0.0f),
		const btVector3 scale = btVector3(1.0f, 1.0f, 1.0f))
	{
		m_shouldBeUpdated = true;
		m_transform = nullptr;
		m_shouldBeDestroyed = false;

		// We setup the transform -> Every GameObject has a transform
		AddComponent(XDGameEngine::ComponentFactory::CreateComponent('TRFM', *this, pos, rot, scale));
		m_transform = GetComponent<Transform>();

		this->m_transform->setPosition(pos);
		this->m_transform->setRotation(rot);
		this->m_transform->setScale(scale);
	}

	GameObject::~GameObject()
	{
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