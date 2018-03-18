#pragma once
#include "GLM/glm.hpp"
#include <string>

#include "FontType.h"

class GUIText {
private:
	std::string m_TextString;
	float m_FontSize;

	int m_TextMeshVao;
	int m_VertexCount;
	glm::vec3 m_Colour = { 0.0f, 0.0f, 0.0f };

	glm::vec2 m_Position;
	float m_LineMaxSize;
	int m_NumberOfLines;

	FontType m_Font;

	bool m_CenterText = false;

public:
	GUIText(const std::string& text, float fontSize, FontType font, glm::vec2 position, float maxLineLength, bool centered)
		: m_TextString(text), m_FontSize(fontSize), m_Font(font), m_Position(position), m_LineMaxSize(maxLineLength), m_CenterText(centered)
	{
		TextMaster.LoadText(this);
	}

	void Remove()
	{
		TextMaster.RemoveText(this);
	}

	FontType GetFont()
	{
		return m_Font;
	}

	void SetColour(float r, float g, float b)
	{
		m_Colour = { r, g, b };
	}

	glm::vec3 GetColour()
	{
		return m_Colour;
	}

	int GetNumberOfLines()
	{
		return m_NumberOfLines;
	}

	glm::vec2 GetPosition()
	{
		return m_Position;
	}

	int GetMesh()
	{
		return m_TextMeshVao;
	}

	void SetMeshInfo(int vao, int verticesCount)
	{
		m_TextMeshVao = vao;
		m_VertexCount = verticesCount;
	}

	int GetVertexCount()
	{
		return m_VertexCount;
	}

	float GetFontSize()
	{
		return m_FontSize;
	}

	void SetNumberOfLines(int number)
	{
		m_NumberOfLines = number;
	}

	bool IsCentered()
	{
		return m_CenterText;
	}

	float GetMaxLineSize()
	{
		return m_LineMaxSize;
	}

	const std::string& GetTextString()
	{
		return m_TextString;
	}

};