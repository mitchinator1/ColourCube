#include "UITextBox.h"
#include "../../Mesh/Mesh.h"
#include "GLFW/glfw3.h"

namespace UI
{
	UITextBox::UITextBox() noexcept
		: UIText(), m_TextSpeed(2.5f / 100.0f), m_CurrentCharCount(0)
	{
		m_UpdateNeeded = true;
		SetSize(1.5f);
	}

	UITextBox::~UITextBox()
	{
		
	}

	void UITextBox::Update()
	{
		if (m_Hidden)
		{
			m_UpdateNeeded = false;
			return;
		}
		if (m_TotalChar > m_CurrentCharCount)
		{
			m_Time = (float)glfwGetTime();
			if (m_Time - m_PrevTime > m_TextSpeed)
			{
				m_CurrentCharCount += 6;
				m_Mesh->UpdateCount(m_CurrentCharCount);
				m_PrevTime = m_Time;
			}
		}
		else
		{
			m_UpdateNeeded = false;
		}
	}

	bool UITextBox::Continue()
	{
		if (m_CurrentCharCount < m_TotalChar)
		{
			m_CurrentCharCount = m_TotalChar;
			m_Mesh->UpdateCount(m_CurrentCharCount);
			return true;
		}
		else
		{
			m_Mesh.reset();
			++m_KeyNumber;
			LoadText();
			m_CurrentCharCount = 0;
			if (GetTextString().empty())
				return false;
		}
		return true;
	}

}
