#include "UIElement.h"
#include "../Mesh/Mesh.h"
#include <iostream>

namespace UI
{
	UIElement::UIElement()
		: minX(0.0f), minY(0.0f), maxX(0.0f), maxY(0.0f)
		, m_Colour{ 1.0f, 1.0f, 1.0f }, m_Alpha(1.0f), m_Depth(0.0f)
		, m_Mesh(nullptr), m_Position({ 0.0f, 0.0f, 0.0f })
	{

	}

	UIElement::UIElement(float x, float y, float xSize, float ySize)
		: minX(x / 50.0f - 1.0f), minY(-y / 50.0f + 1.0f), maxX((x + xSize) / 50.0f - 1.0f), maxY(-(y + ySize) / 50.0f + 1.0f)
		, m_Colour{ 1.0f, 1.0f, 1.0f }, m_Alpha(1.0f), m_Depth(0.0f)
		, m_Mesh(nullptr), m_Position({ 0.0f, 0.0f, 0.0f })
	{

	}

	UIElement::~UIElement()
	{

	}

	void UIElement::Bind()
	{
		m_Mesh->Bind();
	}

	void UIElement::Unbind()
	{
		m_Mesh->Unbind();
	}

	UIElement* UIElement::SetMin(float x, float y)
	{
		minX = x / 50.0f - 1.0f;
		minY = -y / 50.0f + 1.0f;
		return this;
	}

	UIElement* UIElement::SetMax(float x, float y)
	{
		float xmin = (minX + 1.0f) * 50.0f;
		maxX = (xmin + x) / 50.0f - 1.0f;

		float ymin = -(minY - 1.0f) * 50.0f;
		maxY = -(ymin + y) / 50.0f + 1.0f;

		return this;
	}

	UIElement* UIElement::SetColour(float r, float g, float b)
	{
		m_Colour = { r, g, b };
		return this;
	}

	UIElement* UIElement::SetAlpha(float alpha)
	{
		m_Alpha = alpha;
		return this;
	}

	UIElement* UIElement::SetDepth(float depth)
	{
		m_Depth = depth;
		return this;
	}

	UIElement* UIElement::SetPosition(glm::vec3 position)
	{
		m_Position = position;
		return this;
	}

	UIElement* UIElement::SetValue(float value)
	{
		m_Value = value;
		m_Alpha = value;
		float xpos = m_Value * m_Width;
		SetPosition({ xpos, 0.0f, 0.0f });
		return this;
	}

	UIElement* UIElement::SetWidth(float width)
	{
		m_Width = width / 50.0f;
		return this;
	}

	UIElement* UIElement::SetAction(ACTION action)
	{
		m_Action = action;
		return this;
	}

	void UIElement::Build()
	{
		m_Mesh = std::make_unique<Mesh>(CalculateVertices(), 2, 3);
	}

	unsigned int UIElement::GetCount()
	{
		return m_Mesh->GetCount();
	}

	std::vector<float> UIElement::CalculateVertices()
	{
		const auto& c = m_Colour;

		std::vector<float> vertices{
			minX,	minY,	m_Depth,		c.r, c.g, c.b,
			minX,	maxY,	m_Depth,		c.r, c.g, c.b,
			maxX,	maxY,	m_Depth,		c.r, c.g, c.b,
			maxX,	minY,	m_Depth,		c.r, c.g, c.b,
		};

		return vertices;
	}
}