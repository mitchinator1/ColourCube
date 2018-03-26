#ifndef TEXT_MESH_CREATOR_H
#define TEXT_MESH_CREATOR_H
#include "Line.h"
//#include "TextMeshData.h"

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
		~TextMeshCreator();

		std::vector<float> CreateVertexData(GUIText& text);

	private:
		std::vector<Line> CreateStructure(GUIText& text);
		void CompleteStructure(std::vector<Line>& lines, Line currentLine, Word currentWord, GUIText& text);
		std::vector<float> CreateQuadVertices(GUIText& text, std::vector<Line>& lines);

	};
}

#endif