#include "UISlider.h"

namespace UI
{
	UISlider::UISlider() noexcept
	{
		m_Position.z -= 0.1f;
	}

	UISlider::~UISlider()
	{

	}

	void UISlider::Update()
	{
		if (m_IsVertical)
		{
			float newY = m_Position.y + ySize * m_Value - (m_Elements.back()->ySize / 2.0f);
			m_Elements.back()->GetPosition().y = newY;

			if (m_Elements.back()->GetPosition().y <= m_Position.y)
			{
				newY = m_Position.y;
			}

			if (m_Elements.back()->GetPosition().y >= m_Position.y + ySize - m_Elements.back()->ySize)
			{
				newY = m_Position.y + ySize - m_Elements.back()->ySize;
			}

			m_Elements.back()->GetPosition().y = newY;
		}
		else
		{
			float newX = m_Position.x + xSize * m_Value - (m_Elements.back()->xSize / 2.0f);
			m_Elements.back()->GetPosition().x = newX;

			if (m_Elements.back()->GetPosition().x <= m_Position.x)
			{
				newX = m_Position.x;
			}

			if (m_Elements.back()->GetPosition().x >= m_Position.x + xSize - m_Elements.back()->xSize)
			{
				newX = m_Position.x + xSize - m_Elements.back()->xSize;
			}

			m_Elements.back()->GetPosition().x = newX;
		}

		if (m_ValuePtr)
			*m_ValuePtr = m_Value;
	}

	bool UISlider::InRange(float x, float y)
	{
		if (x < m_Position.x || x > m_Position.x + xSize)
		{
			return false;
		}
		if (y < m_Position.y || y > m_Position.y + ySize)
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
				if (x >= element->GetPosition().x && x <= element->GetPosition().x + element->xSize)
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
				if (y >= GetPosition().y && y <= element->GetPosition().y + element->ySize)
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
			m_Value = (value - m_Position.y) / ((m_Position.y + ySize) - m_Position.y);
		}
		else
		{
			m_Value = (value - m_Position.x) / ((m_Position.x + xSize) - m_Position.x);
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

		//TODO: Make this element a Drag Bar instead

		auto element = std::make_unique<UI::UIElement>();
		float size = 3.0f;
		if (m_IsVertical)
		{
			element->xSize = xSize;
			element->ySize = size;
		}
		else
		{
			element->xSize = size / 2.0f;
			element->ySize = ySize;
		}
		element->GetPosition().y = element->ySize - size;
		element->GetPosition().z -= 0.05f;
		element->colour = { 0.6f, 0.5f, 0.8f, 1.0f };
		element->Build();
		AddElement(element);

		m_TraitsAdded = true;
	}

}