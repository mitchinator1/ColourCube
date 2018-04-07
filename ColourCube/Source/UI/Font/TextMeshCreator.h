#ifndef TEXT_MESH_CREATOR_H
#define TEXT_MESH_CREATOR_H
#include <string>
#include <vector>
#include <memory>

namespace UI { class UIText; }
namespace Text
{
	class Line;
	class Word;
	class MetaFile;

	class TextMeshCreator
	{
	private:
		std::unique_ptr<MetaFile> m_MetaData;
		const float LINE_HEIGHT = 0.03f;
		const int SPACE_ASCII = 32;

	public:
		TextMeshCreator(const std::string& filepath = "Resources/Font/Arial.fnt");
		~TextMeshCreator();

		std::vector<float> CreateVertexData(UI::UIText& text);

	private:
		std::vector<Line> CreateStructure(UI::UIText& text);
		void CompleteStructure(std::vector<Line>& lines, Line currentLine, Word currentWord, UI::UIText& text);
		std::vector<float> CreateQuadVertices(UI::UIText& text, std::vector<Line>& lines);

	};
}

#endif