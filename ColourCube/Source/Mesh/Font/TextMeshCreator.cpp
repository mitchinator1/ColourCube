#include "TextMeshCreator.h"

#include "GUIText.h"
#include "MetaFile.h"

namespace Text
{
	const float TextMeshCreator::LINE_HEIGHT = 0.03f;
	const int TextMeshCreator::SPACE_ASCII = 32;

	TextMeshCreator::TextMeshCreator(const std::string& filepath)
		: m_MetaData(new MetaFile(filepath))
	{
		
	}

	TextMeshCreator::~TextMeshCreator()
	{
		delete m_MetaData;
	}

	std::vector<float> TextMeshCreator::CreateVertexData(GUIText& text)
	{
		std::vector<Line> lines = CreateStructure(text);
		return CreateQuadVertices(text, lines);
	}

	std::vector<Line> TextMeshCreator::CreateStructure(GUIText& text)
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
			//Character character = m_MetaData->GetCharacter(ascii);
			currentWord.AddCharacter(m_MetaData->GetCharacter(ascii));
			//currentWord.AddCharacter(character);
		}
		CompleteStructure(lines, currentLine, currentWord, text);
		return lines;
	}

	void TextMeshCreator::CompleteStructure(std::vector<Line>& lines, Line currentLine, Word currentWord, GUIText& text)
	{
		if (!currentLine.AttemptToAddWord(currentWord))
		{
			lines.emplace_back(currentLine);
			currentLine = Line(m_MetaData->GetSpaceWidth(), text.GetFontSize(), text.GetMaxLineSize());
			currentLine.AttemptToAddWord(currentWord);
		}
		lines.emplace_back(currentLine);
	}

	std::vector<float> TextMeshCreator::CreateQuadVertices(GUIText& text, std::vector<Line>& lines)
	{
		text.SetNumberOfLines(lines.size()); 
		float curserX = 0.0f;
		float curserY = 0.0f;
		std::vector<float> vertices;
		for (Line& line : lines)
		{
			if (text.IsCentered())
			{
				curserX = (line.GetMaxLength() - line.GetLineLength()) / 2.0f;
			}
			float fontSize = text.GetFontSize();
			for (Word& word : line.GetWords())
			{
				for (Character& letter : word.GetCharacters())
				{
					float x = curserX + (letter.xOffset * fontSize);
					float y = curserY + (letter.yOffset * fontSize);
					float maxX = x + (letter.xSize * fontSize);
					float maxY = y + (letter.ySize * fontSize);
					float properX = (2.0f * x) - 1.0f;
					float properY = (-2.0f * y) + 1.0f;
					float properMaxX = (2.0f * maxX) - 1.0f;
					float properMaxY = (-2.0f * maxY) + 1.0f;
					vertices.insert(vertices.end(),
						{ 
						properX,	properY,		letter.xTextureCoord,	 letter.yTextureCoord,
						properX,	properMaxY,		letter.xTextureCoord,	 letter.yMaxTextureCoord,
						properMaxX, properMaxY,		letter.xMaxTextureCoord, letter.yMaxTextureCoord,
						properMaxX, properY,		letter.xMaxTextureCoord, letter.yTextureCoord
						});
					curserX += letter.xAdvance * fontSize;
				}
				curserX += m_MetaData->GetSpaceWidth() * fontSize;
			}
			curserX = 0.0f;
			curserY += LINE_HEIGHT * fontSize;
		}
		return vertices;
	}

}