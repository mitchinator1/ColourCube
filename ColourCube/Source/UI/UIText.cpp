#include "UIText.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Font/FontType.h"
#include "GLFW/glfw3.h"

namespace UI
{
	UIText::UIText(const std::string& key, unsigned int keyNumber, float fontSize, float x, float y, float maxLineLength, bool centered)
		: m_KeyString(key), m_KeyNumber(keyNumber), m_FontSize(fontSize), m_Position({ x / 100.0f, y / 100.0f })
		, m_LineMaxSize(maxLineLength / 100.0f), m_CenterText(centered)
		, m_NumberOfLines(0), m_Mesh(nullptr)
	{
		LoadText();
	}

	UIText::~UIText()
	{
		
	}
	
	void UIText::CreateMesh(const Text::FontType* font)
	{
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
		
	}

	bool UIText::Continue()
	{
		m_Mesh.reset();
		++m_KeyNumber;
		LoadText();
		return true;
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
	
	void UIText::SetColour(float r, float g, float b)
	{
		m_Colour = { r, g, b };
	}

	void UIText::SetNumberOfLines(int number)
	{
		m_NumberOfLines = number;
	}

}