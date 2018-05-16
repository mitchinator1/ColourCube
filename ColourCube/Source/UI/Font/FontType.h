#ifndef FONT_TYPE_H
#define FONT_TYPE_H
#include <string>
#include <vector>
#include <memory>

namespace UI { class UIText; }
class Texture;

namespace Text
{
	class TextMeshCreator;

	class FontType {
	private:
		std::string m_FontName;
		std::unique_ptr<TextMeshCreator> m_Loader;
		std::unique_ptr<Texture> m_Texture;

	public:
		FontType(const std::string& fontFile = "Arial") noexcept;
		~FontType();

		void Bind() const;
		void Unbind() const;

		std::vector<float> LoadText(UI::UIText& text) const;

		const std::string& GetName() const { return m_FontName; }

		bool operator==(const FontType& rhs) const;
		bool operator==(const std::string& name) const;
	};
}

#endif