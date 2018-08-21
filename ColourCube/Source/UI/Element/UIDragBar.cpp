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
		if (x >= m_Position.x && y >= m_Position.y && x <= m_Position.x + xSize && y <= m_Position.y + ySize)
		{
			if (!IsMouseOver()) OnMouseOver();

			if (IsMouseDown())
			{
				x = x - m_Position.x - xSize / 2.0f;
				x += m_Position.x;

				y = y - m_Position.y - ySize / 2.0f;
				y += m_Position.y;

				m_Parent->SetPosition({ x, y, m_Parent->GetPosition().z });
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