#include "TextMeshCreator.h"

#include "GUIText.h"
#include "MetaFile.h"

namespace Text
{
	const float TextMeshCreator::LINE_HEIGHT = 0.03f;
	const int TextMeshCreator::SPACE_ASCII = 32;

	TextMeshCreator::TextMeshCreator(const std::string& filepath)
	//	: m_MetaData(filepath)
	{
		m_MetaData = new MetaFile(filepath);
	}

	TextMeshData TextMeshCreator::CreateTextMesh(GUIText& text)
	{
		std::vector<Line> lines = CreateStructure(text);
		TextMeshData data = CreateQuadVertices(text, lines);
		return data;
	}

	std::vector<Line> TextMeshCreator::CreateStructure(GUIText& text)
	{
		//char[] chars = text.GetTextString().ToCharArray();
		std::string chars = text.GetTextString();
		std::vector<Line> lines;
		Line currentLine(m_MetaData->GetSpaceWidth(), text.GetFontSize(), text.GetMaxLineSize());
		Word currentWord(text.GetFontSize());

		for (char& c : chars)
		{
			int ascii = (int)c;
			if (ascii == SPACE_ASCII)
			{
				bool added = currentLine.AttemptToAddWord(currentWord);
				if (!added)
				{
					lines.emplace_back(currentLine);
					currentLine = Line(m_MetaData->GetSpaceWidth(), text.GetFontSize(), text.GetMaxLineSize());
					currentLine.AttemptToAddWord(currentWord);
				}
				currentWord = Word(text.GetFontSize());
				continue;
			}
			Character character = m_MetaData->GetCharacter(ascii);
			currentWord.AddCharacter(character);
		}
		CompleteStructure(lines, currentLine, currentWord, text);
		return lines;
	}

	void TextMeshCreator::CompleteStructure(std::vector<Line>& lines, Line currentLine, Word currentWord, GUIText& text)
	{
		bool added = currentLine.AttemptToAddWord(currentWord);
		if (!added) {
			lines.emplace_back(currentLine);
			currentLine = Line(m_MetaData->GetSpaceWidth(), text.GetFontSize(), text.GetMaxLineSize());
			currentLine.AttemptToAddWord(currentWord);
		}
		lines.emplace_back(currentLine);
	}

	TextMeshData TextMeshCreator::CreateQuadVertices(GUIText& text, std::vector<Line>& lines)
	{
		text.SetNumberOfLines(lines.size());
		float curserX = 0.0f;
		float curserY = 0.0f;
		std::vector<float> vertices;
		std::vector<float> textureCoords;
		for (Line& line : lines)
		{
			if (text.IsCentered())
			{
				curserX = (line.GetMaxLength() - line.GetLineLength()) / 2.0f;
			}
			for (Word& word : line.GetWords())
			{
				for (Character& letter : word.GetCharacters())
				{
					AddVerticesForCharacter(curserX, curserY, letter, text.GetFontSize(), vertices);
					AddTexCoords(textureCoords, letter.xTextureCoord, letter.yTextureCoord, letter.xMaxTextureCoord, letter.yMaxTextureCoord);
					curserX += letter.xAdvance * text.GetFontSize();
				}
				curserX += m_MetaData->GetSpaceWidth() * text.GetFontSize();
			}
			curserX = 0.0f;
			curserY += LINE_HEIGHT * text.GetFontSize();
		}
		return TextMeshData(vertices, textureCoords);
	}

	void TextMeshCreator::AddVerticesForCharacter(float curserX, float curserY, Character& character, float fontSize, std::vector<float>& vertices)
	{
		float x = curserX + (character.xOffset * fontSize);
		float y = curserY + (character.yOffset * fontSize);
		float maxX = x + (character.xSize * fontSize);
		float maxY = y + (character.ySize * fontSize);
		float properX = (2 * x) - 1;
		float properY = (-2 * y) + 1;
		float properMaxX = (2 * maxX) - 1;
		float properMaxY = (-2 * maxY) + 1;
		AddVertices(vertices, properX, properY, properMaxX, properMaxY);
	}

	/*static*/ void TextMeshCreator::AddVertices(std::vector<float>& vertices, float x, float y, float maxX, float maxY)
	{
		//TODO: change to insert
		vertices.emplace_back(x);
		vertices.emplace_back(y);
		vertices.emplace_back(x);
		vertices.emplace_back(maxY);
		vertices.emplace_back(maxX);
		vertices.emplace_back(maxY);
		vertices.emplace_back(maxX);
		vertices.emplace_back(maxY);
		vertices.emplace_back(maxX);
		vertices.emplace_back(y);
		vertices.emplace_back(x);
		vertices.emplace_back(y);
	}

	/*static*/ void TextMeshCreator::AddTexCoords(std::vector<float>& texCoords, float x, float y, float maxX, float maxY)
	{
		//TODO: change to insert
		texCoords.emplace_back(x);
		texCoords.emplace_back(y);
		texCoords.emplace_back(x);
		texCoords.emplace_back(maxY);
		texCoords.emplace_back(maxX);
		texCoords.emplace_back(maxY);
		texCoords.emplace_back(maxX);
		texCoords.emplace_back(maxY);
		texCoords.emplace_back(maxX);
		texCoords.emplace_back(y);
		texCoords.emplace_back(x);
		texCoords.emplace_back(y);
	}

}