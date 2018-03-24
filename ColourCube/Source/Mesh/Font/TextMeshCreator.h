#pragma once
#include "Line.h"
#include "TextMeshData.h"

#include <string>
#include <vector>


namespace Text
{
	class GUIText;
	class MetaFile;

	class TextMeshCreator
	{
	public:
		const static float LINE_HEIGHT;
		const static int SPACE_ASCII;

	private:
		MetaFile* m_MetaData;

	public:
		TextMeshCreator(const std::string& filepath = "Resources/Font/Arial.fnt");

		TextMeshData CreateTextMesh(GUIText& text);

	private:
		std::vector<Line> CreateStructure(GUIText& text);
		void CompleteStructure(std::vector<Line>& lines, Line currentLine, Word currentWord, GUIText& text);
		TextMeshData CreateQuadVertices(GUIText& text, std::vector<Line>& lines);

		void AddVerticesForCharacter(float curserX, float curserY, Character& character, float fontSize, std::vector<float>& vertices);
		void AddVertices(std::vector<float>& vertices, float x, float y, float maxX, float maxY);
		void AddTexCoords(std::vector<float>& texCoords, float x, float y, float maxX, float maxY);
	};
}