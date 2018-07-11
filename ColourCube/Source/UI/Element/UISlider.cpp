#include "UISlider.h"

namespace UI
{
	UISlider::UISlider() noexcept
	{

	}

	UISlider::~UISlider()
	{

	}

	void UISlider::Update()
	{
		float newX = (maxX / 50.0f) * m_Value - ((m_Elements.back()->maxX / 2.0f) / 100.0f);
		m_Elements.back()->SetPosition({ newX, 0.0f, 0.0f });

		if (m_ValuePtr)
			*m_ValuePtr = m_Value;
	}

	ACTION UISlider::OnMouseDown()
	{
		if (IsMouseOver())
		{
			m_IsMouseDown = true;
		}
		return m_MouseDown;
	}

	ACTION UISlider::OnMouseUp()
	{
		if (IsMouseDown())
		{
			m_IsMouseDown = false;
		}
		return m_MouseUp;
	}

	bool UISlider::InRange(float x, float y)
	{
		if (x < minX - 0.01f || x > minX + maxX + 0.01f)
		{
			return false;
		}

		for (auto& box : m_Elements)
		{
			if (box->IsHidden())
			{
				continue;
			}

			if (y >= box->minY && y <= box->minY + box->maxY)
			{
				if (!IsMouseOver())
				{
					m_IsMouseOver = true;
					return true;
				}

				if (IsMouseDown())
				{
					UpdateValue(x);
					Update();
				}
				return true;
			}
			m_IsMouseOver = false;
		}

		return false;
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

	UISlider* UISlider::SetValueRange(float min, float max)
	{
		m_ValueMin = min;
		m_ValueMax = max;
		return this;
	}

	void UISlider::UpdateValue(float value)
	{
		m_Value = (value - minX) / ((minX + maxX) - minX);
		if (m_ValuePtr)
			*m_ValuePtr = m_Value;
	}

	void UISlider::Build()
	{
		if (!m_Mesh)
		{
			std::vector<unsigned int> strides = { 3, 4 };
			m_Mesh = std::make_unique<Mesh>(CalculateVertices(), strides);
		}

		for (auto& element : m_Elements)
		{
			element->minX += minX;
			element->minY = minY - (element->maxY / 2.0f) + (maxY / 2.0f);
			element->Build();
		}

		if (m_Hidden)
		{
			for (auto& element : m_Elements)
				element->Hide();

			if (m_Text)
				m_Text->Hide();
		}

		if (m_Text)
		{
			if (m_Text->IsCentered())
			{
				m_Text->SetPosition(minX + (maxX / 2.0f) - 50.0f, minY)->SetCenter(true);
			}
			else
			{
				m_Text->SetPosition(minX + m_Text->GetPosition().x, minY + m_Text->GetPosition().y);
			}
		}
	}

}