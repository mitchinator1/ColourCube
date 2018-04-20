#include "UITextBox.h"
#include <iostream>
#include "GLFW/glfw3.h"

namespace UI
{
	UITextBox::UITextBox(const std::string& text, float textSpeed)
		: UIText(text, 1.5f, 7.5f, 65.0f, 85.0f, false), m_TextSpeed(textSpeed / 100.0f)
		, m_HitBox(ACTION::CONTINUE, 5.0f, 60.0f, 90.0f, 95.0f)
		, m_CurrentCharCount(0)
	{
		m_UpdateNeeded = true;
	}

	UITextBox::~UITextBox()
	{
		m_HitBox.~UIHitBox();
	}

	void UITextBox::Update()
	{
		//m_TotalChar = GetCount();
		//m_Mesh->UpdateCount(m_CurrentCharCount);
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
}
