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
		std::shared_ptr<Texture> m_Texture;

	public:
		FontType(const std::string& fontFile = "Arial", double width = 1920.0, double height = 1200.0) noexcept;
		~FontType();

		std::vector<float> LoadText(UI::UIText& text)	const;

		std::shared_ptr<Texture>& GetTexture();
		const std::string& GetName()					const { return m_FontName; }

		bool operator==(const FontType& rhs)			const  
		{
			return (m_FontName == rhs.m_FontName);
		}
		bool operator==(const std::string& name)		const  
		{
			return (m_FontName == name);
		}
	};
}

#endif