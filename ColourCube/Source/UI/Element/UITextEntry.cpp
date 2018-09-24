#include "UITextEntry.h"
#include <iostream>

namespace UI
{
	UITextEntry::UITextEntry()
	{

	}

	UITextEntry::~UITextEntry()
	{

	}

	ACTION UITextEntry::OnMouseUp()
	{
		if (m_IsMouseDown)
		{
			if (!m_Activated)
			{
				std::cout << "Activated\n";
				m_Activated = true;
			}
			m_IsMouseDown = false;
		}
		return ACTION::NONE;
	}
}