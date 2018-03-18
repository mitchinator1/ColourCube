#pragma once
#include <string>
#include "TextMeshCreator.h"

class FontType {
private:
	int m_TextureAtlas;
	TextMeshCreator m_Loader;

public:
	FontType(int textureAtlas, const std::string& fontFile)
	: m_TextureAtlas(textureAtlas), m_Loader(fontFile)
	{

	}

	int getTextureAtlas()
	{
		return m_TextureAtlas;
	}

	TextMeshData loadText(GUIText text) {
		return m_Loader.CreateTextMesh(text);
	}

};