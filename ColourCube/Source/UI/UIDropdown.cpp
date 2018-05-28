#include "UIDropdown.h"
#include "UIButton.h"
#include "UIText.h"

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
		if (x >= minX && y <= minY &&
			x <= width && y >= height)
		{
			return true;
		}

		for (auto& box : m_Elements)
		{
			if (box->IsHidden())
			{
				continue;
			}
			if (box->InRange(x, y))
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

	void UIDropdown::AddText(std::shared_ptr<UIText>& text)
	{
		m_Text = text;
	}

	ACTION UIDropdown::OnMouseOver()
	{
		if (!m_IsMouseOver)
		{
			if (GetAlpha() != 0.5f)
				SetAlpha(0.5f);

			Reveal();
			m_IsMouseOver = true;
		}
		return ACTION::NONE;
	}

	ACTION UIDropdown::OnMouseOut()
	{
		if (m_IsMouseOver)
		{
			if (GetAlpha() < 0.6f)
				SetAlpha(m_PersistantAlpha);

			Hide(false);
			m_IsMouseOver = false;
			for (auto& element : m_Elements)
			{
				element->OnMouseOut();
			}
		}
		return ACTION::NONE;
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

		if (m_Text != nullptr)
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
			if (m_Text)
				m_Text->Hide();
		}
	}

}