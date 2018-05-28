#include "UIElement.h"
#include "../Mesh/Mesh.h"
#include <iostream>

namespace UI
{
	UIElement::UIElement() noexcept
		: minX(0.0f), minY(0.0f), maxX(0.0f), maxY(0.0f)
		, colour{ 1.0f, 1.0f, 1.0f }, m_Position({ 0.0f, 0.0f, 0.0f })
		, m_Mesh(nullptr), width(0.0f), height(0.0f), m_Alpha(1.0f), m_PersistantAlpha(1.0f), m_Depth(0.0f)
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

	void UIElement::Update()
	{
		if (m_Mesh)
		{
			m_Mesh->UpdateVertices(CalculateVertices());
		}
	}

	bool UIElement::InRange(float x, float y)
	{
		return false;
	}

	void UIElement::Reveal(bool reveal)
	{
		if (m_Text)
		{
			m_Text->Reveal();
		}

		m_Hidden = false;
	}

	void UIElement::Hide(bool hide)
	{
		if (m_Text)
		{
			m_Text->Hide();
		}
		m_Hidden = true;
	}

	unsigned int UIElement::GetCount()
	{
		return m_Mesh->GetCount();
	}

	ACTION UIElement::OnMouseOver()
	{
		if (!m_IsMouseOver)
		{
			if (m_Alpha != 0.5f)
				SetAlpha(0.5f);

			m_IsMouseOver = true;
		}
		return m_MouseOver;
	}

	ACTION UIElement::OnMouseOut()
	{
		if (m_Alpha < 0.6f)
			SetAlpha(m_PersistantAlpha);

		m_IsMouseOver = false;

		return m_MouseOut;
	}

	ACTION UIElement::OnMouseDown()
	{
		return m_MouseDown;
	}

	void UIElement::BindValue(float* c)
	{
		//m_ValuePtr = c;
	}

	UIElement* UIElement::SetColour(float r, float g, float b)
	{
		colour = { r, g, b };
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
	
	UIElement* UIElement::SetPersistantAlpha(float alpha)
	{
		m_PersistantAlpha = alpha;
		return this;
	}

	UIElement* UIElement::SetDepth(float depth)
	{
		m_Depth = depth;
		return this;
	}

	UIElement* UIElement::SetPosition(const glm::vec3& position)
	{
		m_Position = position;
		return this;
	}

	UIElement* UIElement::SetValue(float value)
	{
		/*m_Value = value * (m_ValueMin + m_ValueMax);
		float newX = (m_Value / (m_ValueMin + m_ValueMax)) * width - ((maxX - minX) / 2.0f);
		SetPosition({ newX, 0.0f, 0.0f });

		if (m_ValuePtr)
			*m_ValuePtr = m_Value;
*/
		return this;
	}

	UIElement* UIElement::SetValueRange(float min, float max)
	{
		//m_ValueMin = min;
		//m_ValueMax = max;
		return this;
	}

	UIElement* UIElement::SetWidth(float width)
	{
		this->width = width / 50.0f;
		return this;
	}

	UIElement* UIElement::SetHeight(float height)
	{
		this->height = height / 50.0f;
		return this;
	}

	UIElement* UIElement::SetMouseOver(ACTION action)
	{
		m_MouseOver = action;
		return this;
	}

	UIElement* UIElement::SetMouseOver(const std::string& action)
	{
		m_MouseOver = StringToEnum(action);
		return this;
	}
	
	UIElement* UIElement::SetMouseOut(ACTION action)
	{
		m_MouseOut = action;
		return this;
	}

	UIElement* UIElement::SetMouseOut(const std::string& action)
	{
		m_MouseOut = StringToEnum(action);
		return this;
	}

	UIElement* UIElement::SetMouseDown(ACTION action)
	{
		m_MouseDown = action;
		return this;
	}

	UIElement* UIElement::SetMouseDown(const std::string& action)
	{
		m_MouseDown = StringToEnum(action);
		return this;
	}

	void UIElement::Build()
	{
		width = (minX + maxX) / 50.0f - 1.0f;
		minX = minX / 50.0f - 1.0f;
		height = -(minY + maxY) / 50.0f + 1.0f;
		minY = -minY / 50.0f + 1.0f;

		float xmin = (minX + 1.0f) * 50.0f;
		maxX = (xmin + maxX) / 50.0f - 1.0f;

		float ymin = -(minY - 1.0f) * 50.0f;
		maxY = -(ymin + maxY) / 50.0f + 1.0f;

		if (!m_Mesh)
		{
			m_Mesh = std::make_unique<Mesh>(CalculateVertices(), 2, 3);
		}

		/*if (m_Value)
		{
			float newX = (m_Value / (m_ValueMin + m_ValueMax)) * width - ((maxX - minX) / 2.0f);
			SetPosition({ newX, 0.0f, 0.0f });
		}*/
	}

	std::vector<float> UIElement::CalculateVertices()
	{
		const auto& c = colour;

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
		if (value == "Menu")			return ACTION::MENU;
		if (value == "Play")			return ACTION::PLAY;
		if (value == "Editor")			return ACTION::EDITOR;
		if (value == "Settings")		return ACTION::SETTINGS;
		if (value == "Exit")			return ACTION::EXIT;
		if (value == "Continue")		return ACTION::CONTINUE;
		if (value == "Load")			return ACTION::LOAD;
		if (value == "Save")			return ACTION::SAVE;
		if (value == "ShowMenu")		return ACTION::SHOW_MENU;
		if (value == "ShowEdit")		return ACTION::SHOW_EDIT;
		if (value == "ShowColour")		return ACTION::SHOW_COLOUR;
		if (value == "HideMenu")		return ACTION::HIDE_MENU;
		if (value == "HideEdit")		return ACTION::HIDE_EDIT;
		if (value == "HideColour")		return ACTION::HIDE_COLOUR;
		if (value == "Toggle")			return ACTION::TOGGLE;
		if (value == "AddColour")		return ACTION::ADD_COLOUR;

		return ACTION::NONE;
	}

}