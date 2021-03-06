#include "TextMeshCreator.h"
#include "../Element/UIText.h"
#include "Line.h"
#include "MetaFile.h"

namespace Text
{
	TextMeshCreator::TextMeshCreator(const std::string& filepath, double width, double height) noexcept
		: m_MetaData(std::make_unique<MetaFile>(filepath, width, height))
	{
		
	}

	TextMeshCreator::~TextMeshCreator()
	{
		
	}

	std::vector<float> TextMeshCreator::CreateVertexData(UI::UIText& text)
	{
		auto lines = CreateStructure(text);
		return CreateQuadVertices(text, lines);
	}

	std::vector<Line> TextMeshCreator::CreateStructure(UI::UIText& text)
	{
		std::vector<Line> lines;
		Line currentLine(m_MetaData->GetSpaceWidth(), text.GetFontSize(), text.GetMaxLineSize());
		Word currentWord(text.GetFontSize());

		std::string chars = text.GetTextString();
		for (char& c : chars)
		{
			int ascii = (int)c;
			if (ascii == SPACE_ASCII)
			{
				if (!currentLine.AttemptToAddWord(currentWord))
				{
					lines.emplace_back(currentLine);
					currentLine = Line(m_MetaData->GetSpaceWidth(), text.GetFontSize(), text.GetMaxLineSize());
					currentLine.AttemptToAddWord(currentWord);
				}
				currentWord = Word(text.GetFontSize());
				continue;
			}
			currentWord.AddCharacter(m_MetaData->GetCharacter(ascii));
		}
		CompleteStructure(lines, currentLine, currentWord, text);
		return lines;
	}

	void TextMeshCreator::CompleteStructure(std::vector<Line>& lines, Line currentLine, Word currentWord, UI::UIText& text)
	{
		if (!currentLine.AttemptToAddWord(currentWord))
		{
			lines.emplace_back(currentLine);
			currentLine = Line(m_MetaData->GetSpaceWidth(), text.GetFontSize(), text.GetMaxLineSize());
			currentLine.AttemptToAddWord(currentWord);
		}
		lines.emplace_back(currentLine);
	}

	std::vector<float> TextMeshCreator::CreateQuadVertices(UI::UIText& text, std::vector<Line>& lines)
	{
		auto cursor = text.position / 100.0f;
		auto colour = text.colour;
		std::vector<float> vertices;
		for (Line& line : lines)
		{
			if (text.IsCentered())
			{
				cursor.x = cursor.x + (line.GetMaxLength() - line.GetLineLength()) / 2.0f;
			}
			float fontSize = text.GetFontSize();
			for (Word& word : line.GetWords())
			{
				float z = text.position.z;
				for (Character& letter : word.GetCharacters())
				{
					float minX = cursor.x + (letter.xOffset * fontSize);
					float minY = cursor.y + (letter.yOffset * fontSize);
					float maxX = minX + (letter.xSize * fontSize);
					float maxY = minY + (letter.ySize * fontSize);
					minX = minX * 2.0f - 1.0f;
					minY = -minY * 2.0f + 1.0f;
					maxX = maxX * 2.0f - 1.0f;
					maxY = -maxY * 2.0f + 1.0f;
					vertices.insert(vertices.end(),	{ 
						minX,	minY,	z,	letter.xTextureCoord,	 letter.yTextureCoord,		colour.r, colour.g, colour.b,
						minX,	maxY,	z,	letter.xTextureCoord,	 letter.yMaxTextureCoord,	colour.r, colour.g, colour.b,
						maxX,	maxY,	z,	letter.xMaxTextureCoord, letter.yMaxTextureCoord,	colour.r, colour.g, colour.b,
						maxX,	minY,	z,	letter.xMaxTextureCoord, letter.yTextureCoord,		colour.r, colour.g, colour.b
					});
					cursor.x += letter.xAdvance * fontSize;
					z -= 0.001f;
				}
				cursor.x += (m_MetaData->GetSpaceWidth() * fontSize);
			}
			cursor.x = 0.0f;
			cursor.y += LINE_HEIGHT * fontSize;
		}
		return vertices;
	}

}