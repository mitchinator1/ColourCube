#include "GUIText.h"
#include <iostream>

namespace Text
{
	GUIText::GUIText(const std::string& text, float fontSize, std::shared_ptr<FontType> font, glm::vec2 position, float maxLineLength, bool centered)
		: m_TextString(text), m_FontSize(fontSize), m_Font(font), m_Position(position), m_LineMaxSize(maxLineLength), m_CenterText(centered)
		, m_VertexCount(0), m_NumberOfLines(0), m_Mesh(nullptr)
	{
		auto data = m_Font->LoadText(*this);

		std::vector<float> vertices;
		for (unsigned int i = 0; i < data.GetVertexPositions().size(); i += 2)
		{
			vertices.emplace_back(data.GetVertexPositions()[i]);
			vertices.emplace_back(data.GetVertexPositions()[i + 1]);

			vertices.emplace_back(data.GetTextureCoords()[i]);
			vertices.emplace_back(data.GetTextureCoords()[i + 1]);
		}

		m_Mesh = new Mesh(vertices, 2, 2);
		m_VertexCount = vertices.size();

		//TODO: Fix
		//TextMaster.LoadText(this);
	}

	void GUIText::Remove()
	{
		//TODO: Fix
		//TextMaster.RemoveText(this);
	}

	FontType& GUIText::GetFont()
	{
		return *m_Font;
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

	void GUIText::Bind()
	{
		m_Mesh->Bind();
	}

	void GUIText::Unbind()
	{
		m_Mesh->Unbind();
	}

	unsigned int GUIText::GetCount()
	{
		return m_Mesh->GetCount();
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