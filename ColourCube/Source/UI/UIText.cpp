#include "UIText.h"
#include <iostream>
#include "Font/FontType.h"
#include "GLFW/glfw3.h"

namespace UI
{
	UIText::UIText(const std::string& text, float fontSize, float x, float y, float maxLineLength, bool centered)
		: m_TextString(text), m_FontSize(fontSize), m_Position({ x / 100.0f, y / 100.0f })
		, m_LineMaxSize(maxLineLength / 100.0f), m_CenterText(centered)
		, m_NumberOfLines(0), m_Mesh(nullptr)
	{
		m_Created = false;
		m_UpdateNeeded = true;
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

	void UIText::SetText(const std::string& text)
	{
		m_Mesh.reset();
		m_TextString = text;
		m_Created = false;
		m_UpdateNeeded = true;
	}

	void UIText::Continue()
	{

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