#pragma once
#include "../Mesh/Mesh.h"
#include "GLM/glm.hpp"

namespace UI
{
	class UIBackground
	{
	private:
		Mesh* m_Mesh;
		glm::vec3 m_Position;
		glm::vec3 m_Size;

	public:
		UIBackground(glm::vec2 position, glm::vec2 size);
		~UIBackground();

		Mesh* GetMesh();
	private:
		std::vector<float> CalculateVertices(glm::vec2 position, glm::vec2 size);
	};
}