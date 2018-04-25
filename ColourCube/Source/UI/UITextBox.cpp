#include "UITextBox.h"
#include <iostream>
#include "GLFW/glfw3.h"

namespace UI
{
	UITextBox::UITextBox(const std::string& key, unsigned int keyNumber, float textSpeed)
		: UIText(key, keyNumber, 1.5f, 7.5f, 65.0f, 85.0f, false), m_TextSpeed(textSpeed / 100.0f)
		, m_HitBox(std::make_unique<UIHitBox>(ACTION::CONTINUE, 5.0f, 60.0f, 90.0f, 95.0f))
		, m_Background(std::make_unique<UIBackground>(5.0f, 60.0f, 90.0f, 35.0f, glm::vec3{ 0.7f, 0.7f, 1.0f }, 0.7f, -1.0f))
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

	void UITextBox::SetFontName(const std::string& name)
	{
		m_FontName = name;
	}

}
