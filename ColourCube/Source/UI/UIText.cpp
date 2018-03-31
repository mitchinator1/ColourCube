#include "UIText.h"
#include "Font/FontType.h"

namespace UI
{
	UIText::UIText(const std::string& text, float fontSize, std::shared_ptr<Text::FontType> font, float x, float y, float maxLineLength, bool centered)
		: m_TextString(text), m_FontSize(fontSize), m_Font(font), m_Position({ x / 100.0f, y / 100.0f })
		, m_LineMaxSize(maxLineLength / 100.0f), m_CenterText(centered)
		, m_NumberOfLines(0), m_Mesh(new Mesh(m_Font->LoadText(*this), 2, 2))
	{

	}

	void UIText::Bind()
	{
		m_Mesh->Bind();
		//m_Font->Bind();
	}

	void UIText::Unbind()
	{
		//m_Font->Unbind();
		m_Mesh->Unbind();
	}

	void UIText::UpdateIndices()
	{
		//m_Mesh->UpdateIndices();
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