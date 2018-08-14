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
		float newX = m_Position.x + (maxX / 50.0f) * m_Value - ((m_Elements.back()->maxX / 2.0f) / 100.0f);
		m_Elements.back()->SetPosition({ newX, m_Position.y, 0.0f });

		if (m_ValuePtr)
			*m_ValuePtr = m_Value;
	}

	bool UISlider::InRange(float x, float y)
	{
		if (x < minX + (m_Position.x * 50.0f) - 0.01f || x > minX + (m_Position.x * 50.0f) + maxX + 0.01f)
		{
			return false;
		}
		
		for (auto& element : m_Elements)
		{
			if (element->IsHidden())
			{
				continue;
			}

			if (y >= element->minY - (element->GetPosition().y * 50.0f) && y <= element->minY - (element->GetPosition().y * 50.0f) + element->maxY)
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

	void UISlider::Build()
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

		auto element = std::make_unique<UI::UIElement>();
		float size = 2.5f;
		element->maxX = size / 2.0f;
		element->maxY = size * 2.0f;
		element->minX = minX;
		element->minY = minY - (element->maxY / 2.0f) + (maxY / 2.0f);
		element->Z -= Z - 0.05f;
		element->colour = { 0.5f, 0.4f, 0.7f, 1.0f };
		element->Build();
		AddElement(element);

		UpdateTextPosition();
	}

	void UISlider::UpdateValue(float value)
	{
		m_Value = (value - minX - (m_Position.x * 50.0f)) / ((minX + (m_Position.x * 50.0f) + maxX) - (minX + (m_Position.x * 50.0f)));
		if (m_ValuePtr)
			*m_ValuePtr = m_Value;
		m_UpdateNeeded = true;
	}

}