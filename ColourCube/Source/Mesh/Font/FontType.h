#ifndef FONT_TYPE_H
#define FONT_TYPE_H
#include <string>
#include <vector>
#include "TextMeshCreator.h"
#include "../Texture.h"

class Text::GUIText;

namespace Text
{
	class FontType {
	private:
		unsigned int m_TextureAtlas;
		TextMeshCreator* m_Loader;
		Texture m_Texture;

	public:
		FontType(const std::string& fontFile = "Arial");
		~FontType();

		unsigned int GetTextureAtlas() const;
		std::vector<float> LoadText(GUIText& text);

	};
}

#endif