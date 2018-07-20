#include "UIText.h"
#include <fstream>
#include <sstream>
#include "../Font/FontType.h"
#include "../../Mesh/Mesh.h"
#include "GLFW/glfw3.h"

namespace UI
{
	UIText::UIText() noexcept
		: m_FontSize(1.0f), m_Position({ 0.0f, 0.0f }), m_LineMaxSize(100.0f / 100.0f), m_CenterText(false)
		, m_Mesh(nullptr), m_UpdateNeeded(false), m_TotalChar(0)
	{

	}
	
	UIText::~UIText()
	{
		
	}
	
	void UIText::CreateMesh(const Text::FontType* font)
	{
		//TODO: Update if Mesh already exists.
		LoadText();
		std::vector<unsigned int> strides = { 2, 2, 3 };
		m_Mesh = std::make_unique<Mesh>(font->LoadText(*this), strides);
		m_TotalChar = m_Mesh->GetCount();
		m_Created = true;
	}

	void UIText::Update()
	{
		if (m_UpdateNeeded)
		{
			if (m_TargetTime > 0.0f)
			{
				m_Time = (float)glfwGetTime();
				if (m_TargetTime - m_Time <= 0.0f)
				{
					Remove();
					m_UpdateNeeded = true;
				}
			}
			else
			{
				m_UpdateNeeded = false;
			}

		}
	}

	bool UIText::Continue()
	{
		return true;
	}

	void UIText::Reveal()
	{
		m_Hidden = false;
	}

	void UIText::Hide()
	{
		m_Hidden = true;
	}

	void UIText::Added()
	{
		m_Added = true;
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
	
	UIText* UIText::SetPosition(float x, float y)
	{
		m_Position = { x / 100.0f, y / 100.0f };
		m_Created = false;
		return this;
	}

	UIText* UIText::SetSize(float size)
	{
		m_FontSize = size;
		return this;
	}

	UIText* UIText::SetLineSize(float size)
	{
		m_LineMaxSize = size / 100.0f;
		return this;
	}

	UIText* UIText::SetColour(float r, float g, float b)
	{
		m_Colour = { r, g, b };
		return this;
	}

	UIText* UIText::SetFont(const std::string& font)
	{
		m_Font = font;
		return this;
	}

	UIText* UIText::SetKey(const std::string& key)
	{
		m_KeyString = key;
		if (m_Mesh)
		{
			m_Created = false;
		}
		return this;
	}

	UIText* UIText::SetKeyNumber(unsigned int number)
	{
		m_KeyNumber = number;
		if (m_Mesh)
		{
			m_Created = false;
		}
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

	Mesh* UIText::GetMesh()
	{
		return m_Mesh.get();
	}

}