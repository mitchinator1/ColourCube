#include "GUIText.h"
#include <iostream>

namespace Text
{
	GUIText::GUIText(const std::string& text, float fontSize, std::shared_ptr<FontType> font, glm::vec2 position, float maxLineLength, bool centered)
		: m_TextString(text), m_FontSize(fontSize), m_Font(font), m_Position(position), m_LineMaxSize(maxLineLength), m_CenterText(centered)
		, m_NumberOfLines(0), m_Mesh(new Mesh(m_Font->LoadText(*this), 2, 2))
	{

		//TODO: Fix
		//TextMaster.LoadText(this);
	}

	void GUIText::Remove()
	{
		//TODO: Fix
		//TextMaster.RemoveText(this);
	}

	void GUIText::Bind()
	{
		m_Mesh->Bind();
	}

	void GUIText::Unbind()
	{
		m_Mesh->Unbind();
	}

	void GUIText::UpdateIndices()
	{
		//m_Mesh->UpdateIndices();
	}

	void GUIText::SetColour(float r, float g, float b)
	{
		m_Colour = { r, g, b };
	}

	void GUIText::SetNumberOfLines(int number)
	{
		m_NumberOfLines = number;
	}

}