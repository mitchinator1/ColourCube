#pragma once
#include <vector>
#include <unordered_map>
#include "RendererFont.h"
#include "../Mesh/Font/FontType.h"
#include "../Mesh/Font/GUIText.h"

class TextMaster {
private:
	//Loader loader;
	//std::unordered_map<Text::FontType, std::vector<Text::GUIText>> texts;
	//Renderer::RendererFont m_Renderer;

public:
	TextMaster(){}
	//static void init(Loader& theLoader)
	//	: m_Loader(theLoader)
	//{

	//}

	/*static void render()
	{
		m_Renderer.render(texts);
	}

	public static void loadText(Text::GUIText text)
	{
		Text::FontType font = text.getFont();
		Text::TextMeshData data = font.loadText(text);
		int vao = loader.loadToVAO(data.getVertexPositions(), data.getTextureCoords());
		text.setMeshInfo(vao, data.getVertexCount());
		std::vector<Text::GUIText> textBatch = texts.get(font);
		if (textBatch == null) {
			textBatch = new ArrayList<GUIText>();
			texts.put(font, textBatch);
		}
		textBatch.add(text);
	}

	static void removeText(Text::GUIText text)
	{
		std::vector<Text::GUIText> textBatch = texts.get(text.getFont());
		textBatch.remove(text);
		if (textBatch.isEmpty()) {
			texts.remove(texts.get(text.getFont()));
		}
	}*/

};