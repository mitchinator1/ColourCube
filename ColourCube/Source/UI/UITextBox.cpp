#include "UITextBox.h"
#include <iostream>
#include "GLFW/glfw3.h"

namespace UI
{
	UITextBox::UITextBox(const std::string& text, float textSpeed)
		: UIText(text, 1.5f, 7.5f, 65.0f, 85.0f, false), m_TextSpeed(textSpeed / 100.0f)
		, m_HitBox(ACTION::CONTINUE, 5.0f, 60.0f, 90.0f, 95.0f)
		, m_Background(std::make_unique<UIBackground>(5.0f, 60.0f, 90.0f, 35.0f, glm::vec3{ 0.7f, 0.7f, 1.0f }, 0.7f))
		, m_CurrentCharCount(0)
	{
		m_UpdateNeeded = true;
	}

	UITextBox::~UITextBox()
	{
		
	}

	void UITextBox::Update()
	{
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

	void UITextBox::SetText(const std::string& text)
	{
		m_Mesh.reset();
		m_TextString = text;
		m_Created = false;
		m_UpdateNeeded = true;
		m_CurrentCharCount = 0;
	}

	void UITextBox::Continue()
	{
		m_CurrentCharCount = m_TotalChar;
		m_Mesh->UpdateCount(m_CurrentCharCount);
	}

}
