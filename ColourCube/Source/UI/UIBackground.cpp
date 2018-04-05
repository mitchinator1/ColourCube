#include "UIBackground.h"
#include <iostream>

namespace UI
{
	UIBackground::UIBackground(float x, float y, float sizeX, float sizeY, bool centered)
		: m_Position(x, y), m_SizeX(sizeX), m_SizeY(sizeY), m_Centered(centered)
	{
		//m_Vertices = CalculateVertices(m_Position.x, (-2.0f * y) + 1.0f, m_SizeX, m_SizeY);
		m_Mesh = new Mesh(CalculateVertices(m_Position.x, (-2.0f * y) + 1.0f, m_SizeX, m_SizeY), 2, 3);
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

	std::vector<float> UIBackground::CalculateVertices(float x, float y, float sizeX, float sizeY)
	{
		float minX = x - (sizeX / 2.0f);// (2.0f * x) - 1.0f;
		float minY = y;// +(sizeY / 2.0f);// (-2.0f * y) + 1.0f;// -(size / 2.0f);
		float maxX = x + (sizeX / 2.0f);
		float maxY = y - sizeY * 2;

		std::vector<float> vertices{
			minX, minY, 0.0f,		1.0f, 1.0f, 1.0f,
			minX, maxY, 0.0f,		1.0f, 1.0f, 1.0f,
			maxX, maxY, 0.0f,		1.0f, 1.0f, 1.0f,
			maxX, minY, 0.0f,		1.0f, 1.0f, 1.0f,
		};

		return vertices;
	}
}