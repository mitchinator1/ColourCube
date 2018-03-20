#include "GUIText.h"

namespace Text
{
	GUIText::GUIText(const std::string& text, float fontSize, FontType font, glm::vec2 position, float maxLineLength, bool centered)
		: m_TextString(text), m_FontSize(fontSize), m_Font(font), m_Position(position), m_LineMaxSize(maxLineLength), m_CenterText(centered)
	{
		//TODO: Fix
		TextMaster.LoadText(this);
	}

	void GUIText::Remove()
	{
		//TODO: Fix
		TextMaster.RemoveText(this);
	}

	FontType& GUIText::GetFont()
	{
		return m_Font;
	}

	void GUIText::SetColour(float r, float g, float b)
	{
		m_Colour = { r, g, b };
	}

	glm::vec3& GUIText::GetColour()
	{
		return m_Colour;
	}

	int GUIText::GetNumberOfLines()
	{
		return m_NumberOfLines;
	}

	glm::vec2& GUIText::GetPosition()
	{
		return m_Position;
	}

	int GUIText::GetMesh()
	{
		return m_TextMeshVao;
	}

	void GUIText::SetMeshInfo(int vao, int verticesCount)
	{
		m_TextMeshVao = vao;
		m_VertexCount = verticesCount;
	}

	int GUIText::GetVertexCount()
	{
		return m_VertexCount;
	}

	float GUIText::GetFontSize()
	{
		return m_FontSize;
	}

	void GUIText::SetNumberOfLines(int number)
	{
		m_NumberOfLines = number;
	}

	bool GUIText::IsCentered()
	{
		return m_CenterText;
	}

	float GUIText::GetMaxLineSize()
	{
		return m_LineMaxSize;
	}

	const std::string& GUIText::GetTextString()
	{
		return m_TextString;
	}
}