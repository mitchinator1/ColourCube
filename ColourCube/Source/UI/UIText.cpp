#include "UIText.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Font/FontType.h"
#include "GLFW/glfw3.h"

namespace UI
{
	UIText::UIText() 
		: m_KeyNumber(0), m_FontSize(1.0f), m_Position({ 0.0f, 0.0f })
		, m_LineMaxSize(100.0f / 100.0f), m_CenterText(false)
		, m_NumberOfLines(0), m_Mesh(nullptr)
	{

	}

	UIText::UIText(const std::string& key, float x, float y, float maxLineLength)
		: m_KeyString(key), m_KeyNumber(0), m_FontSize(1.0f), m_Position({ x / 100.0f, y / 100.0f })
		, m_LineMaxSize(maxLineLength / 100.0f), m_CenterText(false)
		, m_NumberOfLines(0), m_Mesh(nullptr)
	{
		
	}

	UIText::~UIText()
	{
		
	}
	
	void UIText::CreateMesh(const Text::FontType* font)
	{
		LoadText();
		m_Mesh = std::make_unique<Mesh>(font->LoadText(*this), 2, 2);
		m_TotalChar = GetCount();
		m_Created = true;
	}

	void UIText::Bind() const
	{
		m_Mesh->Bind();
	}

	void UIText::Unbind() const
	{
		m_Mesh->Unbind();
	}

	void UIText::Update()
	{
		if (m_UpdateNeeded)
		{
			if (m_TargetTime > 0)
			{
				m_Time = (float)glfwGetTime();
				if (m_TargetTime - m_Time <= 0)
				{
					Remove();
					m_UpdateNeeded = true;
				}
			}
		}
	}

	bool UIText::Continue()
	{
		return true;
	}

	void UIText::Remove()
	{
		m_RemovalNeeded = true;
	}

	void UIText::LoadText()
	{
		std::ifstream stream("Resources/Text/EN.text");
		std::string line;
		while (std::getline(stream, line))
		{
			if (line.find(GetKey()) != std::string::npos)
			{
				std::istringstream part(line);
				std::getline(part, line, '"');
				stream >> line;
				std::getline(part, line, '"');
				m_TextString = line;
				break;
			}
			if (stream.peek() == EOF)
				m_TextString = "";
		}

		m_Created = false;
		m_UpdateNeeded = true;
	}
	
	void UIText::SetNumberOfLines(int number)
	{
		m_NumberOfLines = number;
	}

	UIText* UIText::SetPosition(float x, float y)
	{
		m_Position = { x / 100.0f, y / 100.0f };
		return this;
	}

	UIText* UIText::SetSize(float size)
	{
		m_FontSize = size;
		return this;
	}

	UIText* UIText::SetColour(float r, float g, float b)
	{
		m_Colour = { r, g, b };
		return this;
	}

	UIText* UIText::SetKey(const std::string& key)
	{
		m_KeyString = key;
		return this;
	}

	UIText* UIText::SetKeyNumber(unsigned int number)
	{
		m_KeyNumber = number;
		return this;
	}

	UIText* UIText::SetTime(float time)
	{
		m_TargetTime = (float)glfwGetTime() + time;
		m_UpdateNeeded = true;
		return this;
	}

	UIText* UIText::SetCenter(bool centered)
	{
		m_CenterText = centered;
		return this;
	}

	UIText* UIText::SetHidden(bool hide)
	{
		m_Hidden = hide;
		return this;
	}
}