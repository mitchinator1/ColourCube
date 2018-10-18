#include "UISlider.h"
#include "UIDragBar.h"

namespace UI
{
	UISlider::UISlider() noexcept
	{
		position.z -= 0.1f;
	}

	UISlider::~UISlider()
	{

	}

	void UISlider::AddElement(std::unique_ptr<UIElement>& element)
	{
		m_Elements.emplace_back(std::move(element));
	}

	void UISlider::AddElement(std::unique_ptr<UIDragBar>& element)
	{
		m_Elements.emplace_back(std::move(element));
	}

	void UISlider::Update()
	{
		if (m_IsVertical)
		{
			float newY = position.y + height * m_Value - (m_Elements.back()->height / 2.0f);
			m_Elements.back()->position.y = newY;

			if (m_Elements.back()->position.y <= position.y)
			{
				newY = position.y;
			}

			if (m_Elements.back()->position.y >= position.y + height - m_Elements.back()->height)
			{
				newY = position.y + height - m_Elements.back()->height;
			}

			m_Elements.back()->position.y = newY;
		}
		else
		{
			float newX = position.x + width * m_Value - (m_Elements.back()->width / 2.0f);
			m_Elements.back()->position.x = newX;

			if (m_Elements.back()->position.x <= position.x)
			{
				newX = position.x;
			}

			if (m_Elements.back()->position.x >= position.x + width - m_Elements.back()->width)
			{
				newX = position.x + width - m_Elements.back()->width;
			}

			m_Elements.back()->position.x = newX;
		}

		if (m_ValuePtr)
			*m_ValuePtr = m_Value;
	}

	bool UISlider::InRange(float x, float y)
	{
		if (x < position.x || x > position.x + width)
		{
			return false;
		}
		if (y < position.y || y > position.y + height)
		{
			return false;
		}
		
		for (auto& element : m_Elements)
		{
			if (element->IsHidden())
			{
				continue;
			}

			if (m_IsVertical)
			{
				if (x >= position.x && x <= element->position.x + element->width)
				{
					if (!IsMouseOver())
					{
						m_IsMouseOver = true;
						return true;
					}

					if (IsMouseDown())
					{
						UpdateValue(y);
						m_UpdateNeeded = true;
					}
					return true;
				}
			}
			else
			{
				if (y >= position.y && y <= element->position.y + element->height)
				{
					if (!IsMouseOver())
					{
						m_IsMouseOver = true;
						return true;
					}

					if (IsMouseDown())
					{
						UpdateValue(x);
						m_UpdateNeeded = true;
					}
					return true;
				}
			}
			m_IsMouseOver = false;
		}

		return false;
	}

	ACTION UISlider::OnMouseDown()
	{
		if (IsMouseOver())
		{
			m_IsMouseDown = true;
		}
		return m_MouseDown;
	}

	UISlider* UISlider::SetValue(float value)
	{
		m_Value = value;
		return this;
	}

	UISlider* UISlider::SetValuePointer(float* value)
	{
		m_ValuePtr = value;
		return this;
	}

	UISlider* UISlider::SetVertical(bool isVertical)
	{
		m_IsVertical = isVertical;
		return this;
	}

	void UISlider::UpdateValue(float value)
	{
		if (m_IsVertical)
		{
			m_Value = (value - position.y) / ((position.y + height) - position.y);
		}
		else
		{
			m_Value = (value - position.x) / ((position.x + width) - position.x);
		}

		if (m_ValuePtr)
			*m_ValuePtr = m_Value;
		m_UpdateNeeded = true;
	}

	void UISlider::AddTraits()
	{
		if (m_TraitsAdded)
		{
			return;
		}

		auto element = std::make_unique<UI::UIDragBar>();
		float size = 3.0f;
		if (m_IsVertical)
		{
			element->width = width;
			element->height = size;
		}
		else
		{
			element->width = size / 2.0f;
			element->height = height;
		}
		element->position.z -= 0.05f;
		element->colour = { 0.6f, 0.5f, 0.8f, 1.0f };
		element->Build();
		AddElement(element);

		m_TraitsAdded = true;
	}

}