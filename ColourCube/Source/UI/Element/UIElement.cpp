#include "UIElement.h"
#include "GLFW/glfw3.h"

namespace UI
{
	UIElement::UIElement() noexcept
		: xSize(0.0f), ySize(0.0f), m_PersistantAlpha(1.0f)
	{
		colour = { 1.0f, 1.0f, 1.0f, 1.0f };
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
		if (x >= position.x && y >= position.y && x <= position.x + xSize && y <= position.y + ySize)
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

		for (auto& element : m_Elements)
		{
			element->Hide();
		}

		if (m_Text)
		{
			m_Text->Hide();
		}
		m_Hidden = true;
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
		m_IsMouseDown = false;

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
		if (!m_IsMouseOver)
			return ACTION::NONE;

		auto action = m_MouseUp;

		for (auto& element : m_Elements)
		{
			if (element->IsMouseDown())
			{
				action = element->OnMouseUp();
				if (action == ACTION::HIDE)
				{
					Hide();
					return ACTION::NONE;
				}
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

	UIElement* UIElement::SetPosition(const glm::vec3& inPosition)
	{
		auto change = inPosition - position;

		position = inPosition;
		UpdateTextPosition();
		
		for (auto& element : m_Elements)
		{
			auto ePos = element->position;
			ePos.x += change.x;
			ePos.y += change.y;
			
			element->SetPosition(ePos);
		}
		m_UpdateNeeded = true;
		return this;
	}

	UIElement* UIElement::SetTime(float time)
	{
		m_Time = (float)glfwGetTime();
		m_TargetTime = m_Time + time;
		m_UpdateNeeded = true;
		return this;
	}

	void UIElement::Build()
	{
		if (m_IsBuilt)
			return;

		AddTraits();

		for (auto& element : m_Elements)
		{
			element->position += position;
			element->Build();
		}

		if (m_Hidden)
		{
			Hide();
		}

		UpdateTextPosition();

		m_IsBuilt = true;
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

	std::string& UIElement::GetParentID()
	{
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
		float xmin	= position.x / 50.0f - 1.0f;
		float ymin	= position.y / -50.0f + 1.0f;
		float z		= position.z;

		float xmax	= xmin + (xSize) / 50.0f;
		float ymax	= ymin - (ySize) / 50.0f;

		const auto& c = colour;

		std::vector<float> vertices{
			xmin,	ymin,	z,		c.r, c.g, c.b, c.a,
			xmin,	ymax,	z,		c.r, c.g, c.b, c.a,
			xmax,	ymax,	z,		c.r, c.g, c.b, c.a,
			xmax,	ymin,	z,		c.r, c.g, c.b, c.a
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
				m_Text->SetPosition(position.x + (xSize / 2.0f) - 50.0f, position.y);
				m_Text->GetPosition().z = position.z - 0.01f;
			}
			else
			{
				m_Text->SetPosition(position.x, position.y);
				m_Text->GetPosition().z = position.z - 0.01f;
			}
		}
	}

}