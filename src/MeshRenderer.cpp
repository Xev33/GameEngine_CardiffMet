#include "MeshRenderer.h"

namespace XDGameEngine
{
	MeshRenderer::MeshRenderer()
	{
		m_id = 'MSRD';
		std::cout << " MESH RENDERER CREATED\n";
	}

	MeshRenderer::~MeshRenderer()
	{
		std::cout << " MESH RENDERER DESTRUCTED\n";
	}

	void MeshRenderer::printUnAutreTruc()
	{
		std::cout << "MESH PRINT UN AUTRE TRUC\n";
	}

}