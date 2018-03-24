#include "UIBackground.h"

namespace UI
{
	UIBackground::UIBackground(glm::vec2 position, glm::vec2 size)
		: m_Mesh(nullptr)
	{
		m_Mesh = new Mesh(CalculateVertices(position, size), 2, 2);
	}

	UIBackground::~UIBackground()
	{

	}

	Mesh* UIBackground::GetMesh()
	{
		return m_Mesh;
	}

	std::vector<float> UIBackground::CalculateVertices(glm::vec2 position, glm::vec2 size)
	{
		std::vector<float> vertices;
		return vertices;
	}
}