#include "UIPopup.h"
#include "UISlider.h"
#include "UIButton.h"
#include <iostream>

namespace UI
{
	UIPopup::UIPopup() noexcept
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

	void UIPopup::Hide(bool hide)
	{
		OnMouseOut();

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

	ACTION UIPopup::OnMouseUp()
	{
		m_IsMouseDown = false;
		for (auto& element : m_Elements)
		{
			if (element->IsMouseDown())
			{
				ACTION action = element->OnMouseUp();
				if (action == ACTION::HIDE)
				{
					Hide();
					m_UpdateNeeded = true;
					return ACTION::NONE;
				}
				return element->OnMouseUp();
			}
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
		float xmin = minX + (m_Position.x * 50.0f);
		float ymin = minY - (m_Position.y * 50.0f);

		if (x >= xmin && y >= ymin && x <= xmin + maxX && y <= ymin + maxY)
		{
			if (!IsMouseOver())
				OnMouseOver();
			if (IsMouseDown())
			{
				if (y < ymin + 3.0f)
				{
					x = (x / 50.0f) - 1.0f;
					y = ((-y - 8.0f) / 50.0f) + 1.0f;
					SetPosition({ x, y, 0.0f });
					m_UpdateNeeded = true;
				}
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

	glm::vec4& UIPopup::GetColour()
	{
		return m_Elements.front()->GetColour();
	}

}