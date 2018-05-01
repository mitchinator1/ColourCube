#include "UIBackground.h"
#include "../Mesh/Mesh.h"

namespace UI
{
	UIBackground::UIBackground(float x, float y, float xSize, float ySize, glm::vec3 colour, float alpha, float depth)
		: m_X(x), m_Y(y), m_XSize(xSize), m_YSize(ySize), m_Colour(colour), m_Alpha(alpha), m_Depth(depth)
		, m_Mesh(std::make_unique<Mesh>(CalculateVertices(x / 100.0f, y / 100.0f, xSize / 100.0f, ySize / 100.0f, colour), 2, 3))
		, m_Position({ 0.0f, 0.0f, 0.0f })
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

	void UIBackground::SetAlpha(float alpha)
	{
		m_Alpha = alpha;
	}

	void UIBackground::SetPosition(glm::vec3 position)
	{
		m_Position = position;
	}

	unsigned int UIBackground::GetCount()
	{
		return m_Mesh->GetCount();
	}

	std::vector<float> UIBackground::CalculateVertices(float x, float y, float xSize, float ySize, glm::vec3 c)
	{
		float minX = (x * 2.0f) - 1.0f;
		float minY = (-y * 2.0f) + 1.0f;
		float maxX = minX + (xSize * 2.0f);
		float maxY = minY - (ySize * 2.0f);
		float Z = m_Depth;

		std::vector<float> vertices{
			minX, minY, Z,		c.r, c.g, c.b,
			minX, maxY, Z,		c.r, c.g, c.b,
			maxX, maxY, Z,		c.r, c.g, c.b,
			maxX, minY, Z,		c.r, c.g, c.b,
		};

		return vertices;
	}
}