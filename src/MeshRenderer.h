#ifndef MESH_RENDERER_
#define MESH_RENDERER_

#include "AComponent.h"

#include "Ogre.h"

namespace XDGameEngine
{
	class MeshRenderer : public AComponent
	{
	protected:
	private:
		/**
		* The current scene manager
		*/
		Ogre::SceneManager* m_scnMgr;

		/**
		* The file's name to load
		*/
		const char* m_meshFileName;

		/**
		* The mesh pointer to render
		*/
		Ogre::Entity* m_mesh;

		/**
		* The scene node holding the mesh
		*/
		Ogre::SceneNode* m_sceneNode;

	public:
		MeshRenderer();
		~MeshRenderer();

		/**
		* Overrided method from AComponent. Connect the component to the scene manager
		*/
		virtual void SetUpComponent(GameObject& go);

		/**
		* Toggle the mesh rendering in the scene manager
		*/
		virtual void SetActive(bool isActive);

		/**
		* Update the position of rendering according to the gameObject's transform
		*/
		virtual void UpdateComponent(GameObject& go);

		/**
		* Set the mesh file's name to load
		*/
		void SetMeshFileName(const char* name) noexcept;

		/**
		* Change the mesh entity for Ogre
		*/
		void SetMesh(Ogre::Entity* mesh) noexcept;

		/**
		* Set the inner scene node content
		*/
		void SetSceneNode(Ogre::SceneNode* sceneNode) noexcept;

		/**
		* Getter for the mesh file's name
		*/
		const char* GetMeshFileName() const noexcept;

		/**
		* Getter for the current mesh
		*/
		Ogre::Entity* GetMesh() const noexcept;

		/**
		* Getter for the current scene node
		*/
		Ogre::SceneNode* GetSceneNode() const noexcept;

	};
}

#endif