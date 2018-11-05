#include "UIButton.h"

namespace UI
{
	UIButton::UIButton() noexcept
	{
		position.z -= 0.075f;
	}

	UIButton::~UIButton()
	{

	}
		
	void UIButton::AddElement(std::shared_ptr<UIElement>& element)
	{
		m_Elements.emplace_back(std::move(element));
	}

	void UIButton::AddElement(std::shared_ptr<UIButton>& element)
	{
		m_Elements.emplace_back(std::move(element));
	}

	ACTION UIButton::OnMouseOver()
	{
		if (!m_IsMouseOver)
		{
			if (colour.a != 0.7f)
				colour.a = 0.7f;

			m_IsMouseOver = true;
			m_UpdateNeeded = true;
		}
		return m_MouseOver;
	}

	ACTION UIButton::OnMouseOut()
	{
		if (m_IsMouseOver)
		{
			if (colour.a < 0.8f)
				colour.a = m_PersistantAlpha;

			m_IsMouseOver = false;
			m_UpdateNeeded = true;
		}
		return m_MouseOut;
	}

}