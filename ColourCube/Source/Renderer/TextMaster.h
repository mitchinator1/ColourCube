#pragma once
#include <vector>
#include "FontRenderer.h"

class TextMaster {
private:
	Loader loader;
	Map<FontType, std::vector<GUIText>> texts = new HashMap<FontType, std::vector<GUIText>>();
	FontRenderer renderer;

public:
	static void init(Loader& theLoader)
		: m_Loader(theLoader)
	{

	}

	static void render()
	{
		renderer.render(texts);
	}

	public static void loadText(GUIText text)
	{
		FontType font = text.getFont();
		TextMeshData data = font.loadText(text);
		int vao = loader.loadToVAO(data.getVertexPositions(), data.getTextureCoords());
		text.setMeshInfo(vao, data.getVertexCount());
		List<GUIText> textBatch = texts.get(font);
		if (textBatch == null) {
			textBatch = new ArrayList<GUIText>();
			texts.put(font, textBatch);
		}
		textBatch.add(text);
	}

	static void removeText(GUIText text)
	{
		std::vector<GUIText> textBatch = texts.get(text.getFont());
		textBatch.remove(text);
		if (textBatch.isEmpty()) {
			texts.remove(texts.get(text.getFont()));
		}
	}

	static void cleanUp()
	{
		renderer.cleanUp();
	}

};