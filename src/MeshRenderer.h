#ifndef MESH_RENDERER_
#define MESH_RENDERER_

#include "AComponent.h"

#include "Ogre.h"

namespace XDGameEngine
{
	class MeshRenderer : public AComponent
	{
	public:
		MeshRenderer();
		~MeshRenderer();

		virtual void SetUpComponent();
		virtual void SetActive(bool isActive);
		virtual void UpdateComponent(GameObject& go);
		void printUnAutreTruc();

		void SetMeshFileName(const char* name) noexcept;
		void SetMesh(Ogre::Entity* mesh) noexcept;
		void SetSceneNode(Ogre::SceneNode* sceneNode) noexcept;

		const char* GetMeshFileName() const noexcept;
		Ogre::Entity* GetMesh() const noexcept;
		Ogre::SceneNode* GetSceneNode() const noexcept;


	private:
		Ogre::SceneManager* m_scnMgr;
		const char* m_meshFileName;
		Ogre::Entity* m_mesh;
		Ogre::SceneNode* m_sceneNode;

	protected:
	};
}

#endif