#include "UIElement.h"
#include <iostream>
#include "../../Mesh/Mesh.h"
#include "UISlider.h"
#include "GLFW/glfw3.h"

namespace UI
{
	UIElement::UIElement() noexcept
		: minX(0.0f), minY(0.0f), maxX(0.0f), maxY(0.0f)
		, colour{ 1.0f, 1.0f, 1.0f, 1.0f }, m_Position({ 0.0f, 0.0f, 0.0f })
		, m_PersistantAlpha(1.0f), m_Depth(0.0f)
	{

	}

	UIElement::~UIElement()
	{

	}

	void UIElement::Update()
	{
		//TODO: Make function, check m_Elements for updates.
		if (m_TargetTime > 0.0f)
		{
			m_Time = (float)glfwGetTime();
			if (m_TargetTime - m_Time <= 0.0f)
			{
				Hide();
				m_TargetTime = 0.0f;
			}
		}
	}

	bool UIElement::InRange(float x, float y)
	{
		if (x >= minX + (m_Position.x * 50.0f) && y >= minY - (m_Position.y * 50.0f) &&
			x <= minX + (m_Position.x * 50.0f) + maxX && y <= minY - (m_Position.y * 50.0f) + maxY)
		{
			if (!IsMouseOver())
				OnMouseOver();
			return true;
		}

		return false;
	}

	void UIElement::Reveal(bool reveal)
	{
		if (m_Text)
		{
			m_Text->Reveal();
		}

		m_Hidden = false;
		m_UpdateNeeded = true;
	}

	void UIElement::Reveal(const std::string& id)
	{
		if (m_ID == id)
		{
			Reveal();

			if (id == "Alert")
			{
				SetTime(0.75f);
			}
			m_UpdateNeeded = true;
		}
	}

	void UIElement::Hide(bool hide)
	{
		if (m_Text)
		{
			m_Text->Hide();
		}
		OnMouseOut();
		m_Hidden = true;
		m_UpdateNeeded = true;
	}

	ACTION UIElement::OnMouseOver()
	{
		if (!m_IsMouseOver)
			m_IsMouseOver = true;
		return m_MouseOver;
	}

	ACTION UIElement::OnMouseOut()
	{
		if (m_IsMouseOver)
			m_IsMouseOver = false;
		return m_MouseOut;
	}

	ACTION UIElement::OnMouseDown()
	{
		if (IsMouseOver())
		{
			if (!m_IsMouseDown)
			{
				m_IsMouseDown = true;
			}
		}
		return m_MouseDown;
	}

	ACTION UIElement::OnMouseUp()
	{
		if (m_MouseUp == ACTION::TOGGLE)
		{
			unsigned int keyNumber = m_Text->GetKeyNumber() ? 0 : 1;

			m_Text->SetKeyNumber(keyNumber);
			m_UpdateNeeded = true;
		}
		m_IsMouseDown = false;

		return m_MouseUp;
	}

	void UIElement::AddElement(std::unique_ptr<UIElement>& element)
	{
		m_Elements.emplace_back(std::move(element));
	}

	void UIElement::AddText(std::shared_ptr<UIText>& text)
	{
		m_Text = text;
	}

	UIElement* UIElement::SetID(const std::string& id)
	{
		m_ID = id;
		return this;
	}

	UIElement* UIElement::SetColour(float r, float g, float b)
	{
		colour.r = r;
		colour.g = g;
		colour.b = b;
		
		m_UpdateNeeded = true;
		return this;
	}

	UIElement* UIElement::SetAlpha(float alpha)
	{
		colour.a = alpha;
		m_UpdateNeeded = true;
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

	UIElement* UIElement::SetTime(float time)
	{
		m_Time = (float)glfwGetTime();
		m_TargetTime = m_Time + time;
		m_UpdateNeeded = true;
		return this;
	}

	UIElement* UIElement::SetPosition(const glm::vec3& position)
	{
		m_Position = position;
		UpdateTextPosition();

		for (auto& element : m_Elements)
		{
			element->SetPosition(position);
		}
		m_UpdateNeeded = true;
		return this;
	}
	
	UIElement* UIElement::SetMouseOver(const std::string& action)
	{
		m_MouseOver = StringToEnum(action);
		return this;
	}
	
	UIElement* UIElement::SetMouseOut(const std::string& action)
	{
		m_MouseOut = StringToEnum(action);
		return this;
	}

	UIElement* UIElement::SetMouseDown(const std::string& action)
	{
		m_MouseDown = StringToEnum(action);
		return this;
	}

	UIElement* UIElement::SetMouseUp(const std::string& action)
	{
		m_MouseUp = StringToEnum(action);
		return this;
	}

	void UIElement::Build()
	{
		if (m_Hidden)
		{
			for (auto& element : m_Elements)
				element->Hide();

			if (m_Text)
				m_Text->Hide();
		}

		UpdateTextPosition();
	}

	UIElement* UIElement::GetElement(const std::string& id)
	{
		for (auto& element : m_Elements)
		{
			if (element->m_ID == id)
			{
				return this;
			}
		}

		for (auto& element : m_Elements)
		{
			element->GetElement(id);
		}

		return nullptr;
	}

	bool UIElement::IsMouseOver()
	{
		for (auto& element : m_Elements)
		{
			if (element->IsMouseOver())
			{
				return true;
			}
		}
		return m_IsMouseOver;
	}
	
	std::vector<float> UIElement::GetVertices()
	{
		std::vector<float> vertices = CalculateVertices();
		for (auto& element : m_Elements)
		{
			if (element->IsHidden())
				continue;

			std::vector<float> newVertices = element->GetVertices();
			vertices.insert(vertices.end(), newVertices.begin(), newVertices.end());
			element->m_UpdateNeeded = false;
		}
		m_UpdateNeeded = false;
		return vertices;
	}

	bool UIElement::UpdateNeeded()
	{
		for (auto& element : m_Elements)
		{
			if (element->UpdateNeeded())
			{
				return true;
			}
		}
		if (m_TargetTime > 0.0f)
		{
			m_UpdateNeeded = true;
		}
		return m_UpdateNeeded;
	}

	void UIElement::UpdateFinished()
	{
		for (auto& element : m_Elements)
		{
			element->UpdateFinished();
		}
		if (m_TargetTime - m_Time > 0.0f)
		{
			m_Time = (float)glfwGetTime();
			m_UpdateNeeded = true;
			return;
		}
		m_UpdateNeeded = false;
	}

	std::vector<float> UIElement::CalculateVertices()
	{
		const auto& c = colour;

		float xmin = minX / 50.0f - 1.0f + m_Position.x;
		float ymin = -minY / 50.0f + 1.0f + m_Position.y;

		float xmax = (minX + maxX) / 50.0f -1.0f + m_Position.x;
		float ymax = -(minY + maxY) / 50.0f + 1.0f + m_Position.y;

		std::vector<float> vertices{
			xmin,	ymin,	m_Depth,		c.r, c.g, c.b, c.a,
			xmin,	ymax,	m_Depth,		c.r, c.g, c.b, c.a,
			xmax,	ymax,	m_Depth,		c.r, c.g, c.b, c.a,
			xmax,	ymin,	m_Depth,		c.r, c.g, c.b, c.a
		};

		m_UpdateNeeded = false;
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
		if (value == "Show")			return ACTION::SHOW;
		if (value == "Hide")			return ACTION::HIDE;
		if (value == "Toggle")			return ACTION::TOGGLE;
		if (value == "AddColour")		return ACTION::ADD_COLOUR;
		if (value == "Undo")			return ACTION::UNDO;
		if (value == "Redo")			return ACTION::REDO;

		return ACTION::NONE;
	}

	void UIElement::UpdateTextPosition()
	{
		if (m_Text)
		{
			if (m_Text->IsCentered())
			{
				m_Text->SetPosition(minX + (m_Position.x * 50.0f) + (maxX / 2.0f) - 50.0f, minY - (m_Position.y * 50.0f));
			}
			else
			{
				m_Text->SetPosition(minX + (m_Position.x * 50.0f), minY - (m_Position.y * 50.0f));
			}
		}
	}
}