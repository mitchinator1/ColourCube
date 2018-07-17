#include "UIPopup.h"
#include "UISlider.h"
#include "UIButton.h"

namespace UI
{
	UIPopup::UIPopup()
	{

	}

	UIPopup::~UIPopup()
	{

	}

	void UIPopup::Update()
	{
		for (auto& element : m_Elements)
		{
			element->Update();
		}
	}

	void UIPopup::Reveal(bool reveal)
	{
		if (reveal)
		{
			for (auto& element : m_Elements)
			{
				element->Reveal();
			}
		}

		m_Hidden = false;
		m_UpdateNeeded = true;

		if (m_Text)
			m_Text->Reveal();
	}

	void UIPopup::Hide(bool hide)
	{
		for (auto& element : m_Elements)
		{
			element->Hide();
		}
		if (hide)
		{
			m_Hidden = true;
			m_UpdateNeeded = true;
			if (m_Text)
				m_Text->Hide();
		}
	}

	ACTION UIPopup::OnMouseOut()
	{
		for (auto& element : m_Elements)
		{
			element->OnMouseOut();
		}
		return m_MouseOut;
	}

	ACTION UIPopup::OnMouseDown()
	{
		if (IsMouseOver())
		{
			m_IsMouseDown = true;
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

	ACTION UIPopup::OnMouseUp()
	{
		for (auto& element : m_Elements)
		{
			if (element->IsMouseDown())
			{
				ACTION action = element->OnMouseUp();
				if (action == ACTION::HIDE)
				{
					Hide();
					m_IsMouseDown = false;
					m_UpdateNeeded = true;
					return ACTION::NONE;
				}
				return element->OnMouseUp();
			}
		}
		if (m_IsMouseDown)
		{
			m_IsMouseDown = false;
		}
		return m_MouseUp;
	}

	void UIPopup::AddElement(std::unique_ptr<UIElement>& element)
	{
		m_Elements.emplace_back(std::move(element));
	}

	void UIPopup::AddElement(std::unique_ptr<UISlider>& element)
	{
		if (!m_Elements.empty())
		{
			if (m_Elements.size() == 1)
				element->SetValuePointer(&m_Elements.front()->colour.r);
			if (m_Elements.size() == 2)
				element->SetValuePointer(&m_Elements.front()->colour.g);
			if (m_Elements.size() == 3)
				element->SetValuePointer(&m_Elements.front()->colour.b);
		}

		m_Elements.emplace_back(std::move(element));
	}

	void UIPopup::AddElement(std::unique_ptr<UIButton>& element)
	{
		m_Elements.emplace_back(std::move(element));
	}

	bool UIPopup::InRange(float x, float y)
	{
		if (x >= minX + (m_Position.x * 50.0f) && y >= minY - (m_Position.y * 50.0f) &&
			x <= minX + (m_Position.x * 50.0f) + maxX && y <= minY - (m_Position.y * 50.0f) + maxY)
		{
			if (!IsMouseOver())
				OnMouseOver();
			if (IsMouseDown())
			{
				SetPosition({ 0.1f, 0.05f, 0.0f });
				m_UpdateNeeded = true;
			}
			return true;
		}

		for (auto& element : m_Elements)
		{
			if (element->InRange(x, y))
			{
				return true;
			}
		}

		return false;
	}

	void UIPopup::Build()
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

		if (m_Text)
		{
			if (m_Text->IsCentered())
			{
				m_Text->SetPosition(minX + (maxX / 2.0f) - 50.0f, minY)->SetCenter(true);
			}
			else
			{
				m_Text->SetPosition(minX + m_Text->GetPosition().x, minY + m_Text->GetPosition().y);
			}
		}

	}

	glm::vec4& UIPopup::GetColour()
	{
		return m_Elements.front()->GetColour();
	}

	bool UIPopup::IsMouseDown()
	{
		for (auto& element : m_Elements)
		{
			if (element->IsMouseDown())
				return true;
		}

		return m_IsMouseDown;
	}

	std::string& UIPopup::GetID()
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

}