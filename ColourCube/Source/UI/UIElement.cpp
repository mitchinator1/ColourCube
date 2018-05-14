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

	unsigned int UIElement::GetCount()
	{
		return m_Mesh->GetCount();
	}

	void UIElement::OnMouseOver()
	{
		if (m_Alpha != 0.5f)
			SetAlpha(0.5f);
	}

	void UIElement::OnMouseOut()
	{
		if (m_Alpha != 1.0f)
			SetAlpha(1.0f);
	}

	ACTION UIElement::OnMouseDown()
	{
		return m_Action;
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
		if (m_Mesh)
		{
			m_Mesh->UpdateVertices(CalculateVertices());
		}
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

	UIElement* UIElement::SetHidden(bool hide)
	{
		m_Hidden = hide;
		return this;
	}

	UIElement* UIElement::SetAction(ACTION action)
	{
		m_Action = action;
		return this;
	}

	UIElement* UIElement::SetAction(const std::string& action)
	{
		m_Action = StringToEnum(action);
		return this;
	}

	void UIElement::Build()
	{
		if (!m_Mesh)
			m_Mesh = std::make_unique<Mesh>(CalculateVertices(), 2, 3);
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

	ACTION UIElement::StringToEnum(const std::string& value)
	{
		ACTION action = ACTION::NONE;

		if (value == "Menu")		return ACTION::MENU;
		if (value == "Play")		return ACTION::PLAY;
		if (value == "Editor")		return ACTION::EDITOR;
		if (value == "Settings")	return ACTION::SETTINGS;
		if (value == "Exit")		return ACTION::EXIT;
		if (value == "Load")		return ACTION::LOAD;
		if (value == "Save")		return ACTION::SAVE;
		if (value == "Toggle")		return ACTION::TOGGLE;
		if (value == "Colour")		return ACTION::COLOUR;

		return action;
	}
}