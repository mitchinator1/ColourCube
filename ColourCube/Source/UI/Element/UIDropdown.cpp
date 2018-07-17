#include "UIDropdown.h"
#include "UIButton.h"

namespace UI
{
	UIDropdown::UIDropdown() noexcept
	{

	}

	UIDropdown::~UIDropdown()
	{

	}

	void UIDropdown::Update()
	{
		for (auto& element : m_Elements)
		{
			element->Update();
		}
	}

	bool UIDropdown::InRange(float x, float y)
	{
		if (x >= minX && y >= minY &&
			x <= minX + maxX && y <= minY + maxY)
		{
			return true;
		}

		for (auto& element : m_Elements)
		{
			if (element->IsHidden())
			{
				continue;
			}
			if (element->InRange(x, y))
			{
				return true;
			}
		}

		return false;
	}

	void UIDropdown::AddElement(std::unique_ptr<UIElement>& element)
	{
		m_Elements.emplace_back(std::move(element));
	}

	void UIDropdown::AddElement(std::unique_ptr<UIButton>& element)
	{
		m_Elements.emplace_back(std::move(element));
	}
	
	void UIDropdown::AddElement(std::unique_ptr<UIDropdown>& element)
	{
		m_Elements.emplace_back(std::move(element));
	}

	ACTION UIDropdown::OnMouseOver()
	{
		if (!m_IsMouseOver)
		{
			if (colour.a != 0.7f)
				colour.a = 0.7f;

			Reveal();
			m_IsMouseOver = true;
		}
		return m_MouseOver;
	}

	ACTION UIDropdown::OnMouseOut()
	{
		if (m_IsMouseOver)
		{
			if (colour.a < 0.8f)
				colour.a = m_PersistantAlpha;

			Hide(false);
			m_IsMouseOver = false;
			for (auto& element : m_Elements)
			{
				if (element->IsMouseOver())
					element->OnMouseOut();
			}
		}
		return m_MouseOut;
	}

	ACTION UIDropdown::OnMouseDown()
	{
		for (auto& button : m_Elements)
		{
			if (button->IsMouseOver())
			{
				return button->OnMouseDown();
			}
		}
		return m_MouseDown;
	}

	ACTION UIDropdown::OnMouseUp()
	{
		for (auto& element : m_Elements)
		{
			if (element->IsMouseDown())
			{
				auto action = element->OnMouseUp();
				Hide(false);
				return action;
			}
		}
		return m_MouseUp;
	}

	void UIDropdown::Reveal(bool reveal)
	{
		if (reveal)
		{
			for (auto& element : m_Elements)
			{
				element->Reveal(false);
			}
		}

		m_Hidden = false;
		m_UpdateNeeded = true;

		if (m_Text)
			m_Text->Reveal();
	}

	void UIDropdown::Hide(bool hide)
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

	void UIDropdown::Build()
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

	std::string& UIDropdown::GetID()
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

	bool UIDropdown::IsMouseDown()
	{
		for (auto& element : m_Elements)
		{
			if (element->IsMouseDown())
				return true;
		}

		return m_IsMouseDown;
	}

}