#include "UIButton.h"

namespace UI
{
	UIButton::UIButton() noexcept
	{

	}

	UIButton::~UIButton()
	{

	}

	void UIButton::Update()
	{

	}

	void UIButton::AddElement(std::unique_ptr<UIElement>& element)
	{
		m_Elements.emplace_back(std::move(element));
	}

	void UIButton::AddElement(std::unique_ptr<UIButton>& element)
	{
		m_Elements.emplace_back(std::move(element));
	}

	ACTION UIButton::OnMouseOver()
	{
		if (!m_IsMouseOver)
		{
			if (GetAlpha() != 0.7f)
				SetAlpha(0.7f);

			m_IsMouseOver = true;
		}
		return m_MouseOver;
	}

	ACTION UIButton::OnMouseOut()
	{
		if (m_IsMouseOver)
		{
			if (GetAlpha() < 0.8f)
				SetAlpha(m_PersistantAlpha);

			m_IsMouseOver = false;
		}
		return m_MouseOut;
	}

}