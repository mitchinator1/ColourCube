#include "UISlider.h"

namespace UI
{
	UISlider::UISlider()
	{

	}

	UISlider::~UISlider()
	{

	}

	void UISlider::Update()
	{
		float newX = (maxX / 50.0f) * m_Value - ((m_Elements.back()->maxX / 2.0f) / 100.0f);
		m_Elements.back()->SetPosition({ newX, 0.0f, 0.0f });
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
				UpdateValue(x);
				Update();
				return true;
			}
		}

		return false;
	}

	UISlider* UISlider::SetValue(float value)
	{
		m_Value = value;
		return this;
	}

	UISlider* UISlider::SetValueRange(float min, float max)
	{
		m_ValueMin = min;
		m_ValueMax = max;
		return this;
	}

	ACTION UISlider::OnMouseOver()
	{
		return ACTION::NONE;
	}

	ACTION UISlider::OnMouseOut()
	{
		return ACTION::NONE;
	}

	ACTION UISlider::OnMouseDown()
	{
		return ACTION::NONE;
	}

	void UISlider::UpdateValue(float value)
	{
		m_Value = (value - minX) / ((minX + maxX) - minX);
	}

}