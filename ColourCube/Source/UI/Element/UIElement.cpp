#include "UIElement.h"
#include "GLFW/glfw3.h"

namespace UI
{
	UIElement::UIElement() noexcept
		: minX(0.0f), minY(0.0f), maxX(0.0f), maxY(0.0f)
		, colour{ 1.0f, 1.0f, 1.0f, 1.0f }, m_Position{ 0.0f, 0.0f, 0.0f }
		, m_PersistantAlpha(1.0f), m_Depth(0.0f)
	{

	}

	UIElement::~UIElement()
	{

	}

	void UIElement::Update()
	{
		for (auto& element : m_Elements)
		{
			if (element->UpdateNeeded())
				element->Update();
		}

		//TODO: Make function.
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
		float xmin = minX + (m_Position.x * 50.0f);
		float ymin = minY - (m_Position.y * 50.0f);

		if (x >= xmin && y >= ymin && x <= xmin + maxX && y <= ymin + maxY)
		{
			if (!IsMouseOver())
				OnMouseOver();
			return true;
		}

		for (auto& element : m_Elements)
		{
			if (element->IsHidden()) continue;

			if (element->InRange(x, y))
			{
				return true;
			}
		}

		return false;
	}

	void UIElement::Reveal(bool reveal)
	{
		if (reveal)
		{
			for (auto& element : m_Elements)
			{
				element->Reveal();
			}
		}

		if (m_Text)
			m_Text->Reveal();

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
		OnMouseOut();

		if (m_Text)
		{
			m_Text->Hide();
		}
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
		m_IsMouseOver = false;

		for (auto& element : m_Elements)
		{
			element->OnMouseOut();
		}

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
		for (auto& element : m_Elements)
		{
			if (element->IsMouseOver())
			{
				ACTION action = element->OnMouseDown();
				m_IsMouseDown = true;
				return action;
			}
		}
		return m_MouseDown;
	}

	ACTION UIElement::OnMouseUp()
	{
		m_IsMouseDown = false;
		auto action = m_MouseUp;

		for (auto& element : m_Elements)
		{
			if (element->IsMouseDown())
			{
				action = element->OnMouseUp();
			}
		}

		if (action == ACTION::TOGGLE)
		{
			unsigned int keyNumber = m_Text->GetKeyNumber() ? 0 : 1;

			m_Text->SetKeyNumber(keyNumber);
			m_UpdateNeeded = true;
		}

		return action;
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
	
	void UIElement::Build()
	{
		for (auto& element : m_Elements)
		{
			element->minX += minX;
			element->minY += minY;
			element->Build();
		}

		if (m_Hidden)
		{
			for (auto& element : m_Elements)
				element->Hide();

			if (m_Text)
				m_Text->Hide();
		}

		UpdateTextPosition();
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

	bool UIElement::IsMouseDown()
	{
		for (auto& element : m_Elements)
		{
			if (element->IsMouseDown())
			{
				return true;
			}
		}

		return m_IsMouseDown;
	}

	std::string& UIElement::GetID()
	{
		for (auto& element : m_Elements)
		{
			if (element->IsMouseOver())
			{
				return element->GetID();
			}
		}
		return m_ID;
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