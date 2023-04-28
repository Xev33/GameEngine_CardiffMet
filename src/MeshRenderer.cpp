#include "MeshRenderer.h"
#include "Game.h"
#include "Scene.h"
#include "GameObject.h"
#include "Transform.h"

namespace XDGameEngine
{
	MeshRenderer::MeshRenderer()
	{
		m_id = 'MSRD';
		m_meshFileName = nullptr;

		m_scnMgr = nullptr;
		m_mesh = nullptr;
		m_sceneNode = nullptr;
		std::cout << " MESH RENDERER CREATED\n";
	}

	MeshRenderer::~MeshRenderer()
	{
		m_scnMgr->destroyMovableObject(m_mesh);
		m_scnMgr = nullptr;

		// Throw error by access violation
		//if (m_mesh != nullptr)
		//	delete m_mesh;
		//m_mesh = nullptr;

		//if (m_sceneNode != nullptr)
		//	delete m_sceneNode;
		//m_sceneNode = nullptr;
		std::cout << " MESH RENDERER DESTRUCTED\n";
	}

	void MeshRenderer::SetUpComponent(GameObject& go)
	{
		// we connect the component to the current scene manager
		m_scnMgr = Game::Instance()->getCurrentScene()->getSceneManager();

		// we create nothing it we don't have a mesh file name
		if (m_meshFileName == nullptr)
			return;

		// We attempt to create the mesh if a file name exists
		m_mesh = m_scnMgr->createEntity(m_meshFileName);
		m_sceneNode = m_scnMgr->getRootSceneNode()->createChildSceneNode();
		m_sceneNode->attachObject(m_mesh);
		m_sceneNode->setScale(1.0f, 1.0f, 1.0f);
	}

	void MeshRenderer::UpdateComponent(GameObject& go)
	{
		Transform* trans = go.GetTransform();
		btQuaternion rot = trans->getRotation();

		// Part to only trigger the rescale once
		if (go.ShouldBeScaled() == true)
		{
			float x = trans->getScale().getX();
			float y = trans->getScale().getY();
			float z = trans->getScale().getZ();
			m_sceneNode->setScale(x, y, z);
			go.ResetShouldBeScaled();
		}
		m_sceneNode->setPosition(Ogre::Vector3(trans->getPosition().getX(),
			trans->getPosition().getY(), trans->getPosition().getZ()));
		m_sceneNode->setOrientation(Ogre::Quaternion(rot.getW(), rot.getX(),
			rot.getY(), rot.getZ()));
	}


	void MeshRenderer::SetActive(bool isActive)
	{
		if (isActive == true && m_isActive == false)
		{
			if (m_sceneNode != nullptr)
				m_sceneNode->setVisible(true);
		}
		else if (isActive == false && m_isActive == true)
		{
			if (m_sceneNode != nullptr)
				m_sceneNode->setVisible(false);
		}
		m_isActive = isActive;
	}

	void MeshRenderer::SetMeshFileName(const char* name) noexcept
	{
		m_meshFileName = name;
	}

	void MeshRenderer::SetMesh(Ogre::Entity* mesh) noexcept
	{
		m_mesh = mesh;
	}

	void MeshRenderer::SetSceneNode(Ogre::SceneNode* sceneNode) noexcept
	{
		m_sceneNode = sceneNode;
	}

	const char* MeshRenderer::GetMeshFileName() const noexcept
	{
		return m_meshFileName;
	}

	Ogre::Entity* MeshRenderer::GetMesh() const noexcept
	{
		return m_mesh;
	}

	Ogre::SceneNode* MeshRenderer::GetSceneNode() const noexcept
	{
		return m_sceneNode;
	}
}