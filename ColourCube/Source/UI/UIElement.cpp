#include "UIElement.h"
#include "../Mesh/Mesh.h"
#include <iostream>

namespace UI
{
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