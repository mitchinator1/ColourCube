#include "UITextEntry.h"
#include "GLFW/glfw3.h"

namespace UI
{
	UITextEntry::UITextEntry()
	{
		m_Text = std::make_shared<UI::UIText>();
		m_Text->SetFont("Arial");
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
				Activate();
			}
			m_IsMouseDown = false;
		}
		return ACTION::NONE;
	}
}