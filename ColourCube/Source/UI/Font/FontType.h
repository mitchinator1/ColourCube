#ifndef FONT_TYPE_H
#define FONT_TYPE_H
#include <string>
#include <vector>
#include "../../Mesh/Texture.h"

namespace UI { class UIText; }

namespace Text
{
	class TextMeshCreator;

	class FontType {
	private:
		std::string m_FontName;
		unsigned int m_TextureAtlas;
		TextMeshCreator* m_Loader;
		Texture* m_Texture;

	public:
		FontType(const std::string& fontFile = "Arial");
		~FontType();

		void Bind() const;
		void Unbind() const;

		std::vector<float> LoadText(UI::UIText& text) const;

		const std::string& GetName() const { return m_FontName; }

		bool operator==(const FontType& rhs) const;
		bool operator==(const std::string& name) const;
		bool operator==(const char* name) const;

	};
}

#endif