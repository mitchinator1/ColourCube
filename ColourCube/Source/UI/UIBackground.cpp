#include "UIBackground.h"
#include <iostream>

namespace UI
{
	UIBackground::UIBackground(glm::vec2 position, float size)
	{
		m_Vertices = CalculateVertices(position, size);
	}

	UIBackground::~UIBackground()
	{

	}

	std::vector<float> UIBackground::CalculateVertices(glm::vec2 position, float size)
	{
		//TODO: Fix yellow output colour
		std::vector<float> vertices{
			position.x,				position.y,			1.0f,	1.0f, 1.0f, 1.0f,
			position.x,				position.y + size,	1.0f,	1.0f, 1.0f, 1.0f,
			position.x + size,		position.y + size,	1.0f,	1.0f, 1.0f, 1.0f,
			position.x + size,		position.y,			1.0f,	1.0f, 1.0f, 1.0f
		};

		return vertices;
	}
}