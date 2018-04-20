#include "UIBackground.h"

namespace UI
{
	UIBackground::UIBackground(float x, float y, float xSize, float ySize, glm::vec3 colour, float alpha)
		: m_X(x), m_Y(y), m_XSize(xSize), m_YSize(ySize), m_Colour(colour), m_Alpha(alpha)
		, m_Mesh(std::make_unique<Mesh>(CalculateVertices(x / 100.0f, y / 100.0f, xSize / 100.0f, ySize / 100.0f, colour), 2, 3))
	{
		
	}

	UIBackground::~UIBackground()
	{

	}

	void UIBackground::Bind()
	{
		m_Mesh->Bind();
	}

	void UIBackground::Unbind()
	{
		m_Mesh->Unbind();
	}

	std::vector<float> UIBackground::CalculateVertices(float x, float y, float xSize, float ySize, glm::vec3 c)
	{
		float minX = (x * 2.0f) - 1.0f;
		float minY = (-y * 2.0f) + 1.0f;
		float maxX = minX + (xSize * 2.0f);
		float maxY = minY - (ySize * 2.0f);

		std::vector<float> vertices{
			minX, minY, 0.0f,		c.r, c.g, c.b,
			minX, maxY, 0.0f,		c.r, c.g, c.b,
			maxX, maxY, 0.0f,		c.r, c.g, c.b,
			maxX, minY, 0.0f,		c.r, c.g, c.b,
		};

		return vertices;
	}
}