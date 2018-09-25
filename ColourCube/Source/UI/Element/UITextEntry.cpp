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
			if (!m_Active)
			{
				std::cout << "Activated\n";
				Activate();
			}
			m_IsMouseDown = false;
		}
		return ACTION::NONE;
	}
}