#include "UIButton.h"
#include "UIText.h"

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

	bool UIButton::InRange(float x, float y)
	{
		if (x >= minX && y <= minY &&
			x <= width && y >= height)
		{
			return true;
		}

		return false;
	}

	void UIButton::AddElement(std::unique_ptr<UIElement>& element)
	{
		m_Elements.emplace_back(std::move(element));
	}

	void UIButton::AddText(std::shared_ptr<UIText>& text)
	{
		m_Text = text;
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

	ACTION UIButton::OnMouseDown()
	{
		return m_MouseDown;
	}

}