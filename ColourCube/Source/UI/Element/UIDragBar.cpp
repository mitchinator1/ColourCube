#include "UIDragBar.h"

#include <iostream>

namespace UI
{
	UIDragBar::UIDragBar()
	{
		colour.a = 0.0f;
	}

	UIDragBar::~UIDragBar()
	{

	}

	bool UIDragBar::InRange(float x, float y)
	{
		float xmin = X + (m_Position.x * 50.0f);
		float ymin = Y - (m_Position.y * 50.0f);

		if (x >= xmin && y >= ymin && x <= xmin + maxX && y <= ymin + maxY)
		{
			if (!IsMouseOver()) OnMouseOver();

			if (IsMouseDown())
			{
				x = x / 50.0f - 1.0f - ((X - maxX) / 100.0f);
				//x = (x / 50.0f - 1.0f) - ((X - maxX) / 100.0f);

				//y = (-y/* - maxY * 2.0f*/) / 50.0f + 1.0f - (maxY / 25.0f);// 0.15f;
				//y = (-y / 50.0f + 1.0f) - ((Y + maxY) / 100.0f);
				y = m_Position.y - (maxY / 50.0f) * (-y / 50.0f + 1.0f) + 0.01f;// +((maxY / 2.0f) / 100.0f);
				//y = m_Position.y + (-y / 50.0f + 1.0f) - 0.175f;// +((maxY / 2.0f) / 100.0f);
				std::cout << y << '\n';

				m_Parent->SetPosition({ x, y, 0.0f });
			}

			return true;
		}

		return false;
	}

	void UIDragBar::SetValuePointer(UIElement* element)
	{
		m_Parent = element;
	}

}