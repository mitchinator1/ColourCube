#include "UIDragBar.h"

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
		if (x >= position.x && y >= position.y && x <= position.x + width && y <= position.y + height)
		{
			if (!IsMouseOver()) OnMouseOver();

			if (IsMouseDown())
			{
				x = x - position.x - width / 2.0f;
				x += position.x;

				y = y - position.y - height / 2.0f;
				y += position.y;

				m_Parent->SetPosition({ x, y, m_Parent->position.z });
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