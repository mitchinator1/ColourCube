#include "UISlider.h"

#include <iostream>

namespace UI
{
	UISlider::UISlider() noexcept
	{
		Z -= 0.1f;
	}

	UISlider::~UISlider()
	{

	}

	void UISlider::Update()
	{
		if (m_IsVertical)
		{
			float newY = m_Position.y - (maxY / 50.0f) * m_Value + ((m_Elements.back()->maxY / 2.0f) / 100.0f);
			m_Elements.back()->SetPosition({ m_Position.x, newY, 0.0f });

			if (m_Elements.back()->GetPosition().y >= m_Position.y)
			{
				newY = m_Position.y;
				m_Elements.back()->SetPosition({ m_Position.x, newY, 0.0f });
			}

			if (m_Elements.back()->GetPosition().y <= m_Position.y - maxY / 50.0f + (m_Elements.back()->maxY / 50.0f))
			{
				newY = m_Position.y - maxY / 50.0f + (m_Elements.back()->maxY / 50.0f);
				m_Elements.back()->SetPosition({ m_Position.x, newY, 0.0f });
			}
		}
		else
		{
			float newX = m_Position.x + (maxX / 50.0f) * m_Value - ((m_Elements.back()->maxX / 2.0f) / 100.0f);
			m_Elements.back()->SetPosition({ newX, m_Position.y, 0.0f });

			if (m_Elements.back()->GetPosition().x <= m_Position.x)
			{
				newX = m_Position.x;
				m_Elements.back()->SetPosition({ newX, m_Position.y, 0.0f });
			}

			if (m_Elements.back()->GetPosition().x >= m_Position.x + maxX / 50.0f - (m_Elements.back()->maxX / 50.0f))
			{
				newX = m_Position.x + maxX / 50.0f - (m_Elements.back()->maxX / 50.0f);
				m_Elements.back()->SetPosition({ newX, m_Position.y, 0.0f });
			}
		}

		if (m_ValuePtr)
			*m_ValuePtr = m_Value;
	}

	bool UISlider::InRange(float x, float y)
	{
		if (x < minX + (m_Position.x * 50.0f) || x > minX + (m_Position.x * 50.0f) + maxX)
		{
			return false;
		}
		if (y < minY - (m_Position.y * 50.0f) || y > minY + (m_Position.y * 50.0f) + maxY)
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
				if (x >= element->minX - (m_Position.x * 50.0f) && x <= element->minX - (m_Position.x * 50.0f) + element->maxX)
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
				if (y >= element->minY - (m_Position.y * 50.0f) && y <= element->minY - (m_Position.y * 50.0f) + element->maxY)
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
			m_Value = (value - minY - (m_Position.y * 50.0f)) / ((minY + (m_Position.y * 50.0f) + maxY) - (minY + (m_Position.y * 50.0f)));
		}
		else
		{
			m_Value = (value - minX - (m_Position.x * 50.0f)) / ((minX + (m_Position.x * 50.0f) + maxX) - (minX + (m_Position.x * 50.0f)));
		}

		if (m_ValuePtr)
			*m_ValuePtr = m_Value;
		m_UpdateNeeded = true;
	}

	void UISlider::AddTraits()
	{
		//TODO: Add horizontal size and vertical size
		auto element = std::make_unique<UI::UIElement>();
		float size = 3.0f;
		if (m_IsVertical)
		{
			element->maxX = maxX;
			element->maxY = size;
		}
		else
		{
			element->maxX = size / 2.0f;
			element->maxY = maxY;
		}
		element->minY = element->maxY - size;
		//element->minY = -(element->maxY / 2.0f) + (maxY / 2.0f);
		element->Z -= 0.05f;
		element->colour = { 0.6f, 0.5f, 0.8f, 1.0f };
		element->Build();
		AddElement(element);
	}

}