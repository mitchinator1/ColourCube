#ifndef META_FILE_H
#define META_FILE_H
#include "Character.h"
#include "../../Utility/FileProgram.h"

namespace Text
{
	class MetaFile : public Utility::FileProgram
	{
	private:
		const int PAD_TOP = 0;
		const int PAD_LEFT = 1;
		const int PAD_BOTTOM = 2;
		const int PAD_RIGHT = 3;
		const int DESIRED_PADDING = 8;
		const float LINE_HEIGHT = 0.03f;
		const int SPACE_ASCII = 32;

		double m_AspectRatio;

		float m_VerticalPerPixelSize;
		float m_HorizontalPerPixelSize;
		float m_SpaceWidth;
		std::vector<int> m_Padding;
		int m_PaddingWidth;
		int m_PaddingHeight;

		std::unordered_map<int, Character> m_MetaData;

	public:
		MetaFile(const std::string& filepath = "Resources/Font/Arial.fnt", double width = 1920.0, double height = 1200.0) noexcept;
		~MetaFile();

		Character& GetCharacter(int ascii);

		auto GetSpaceWidth() { return m_SpaceWidth; }

	private:
		int GetValueOfVariable(const std::string& variable);
		std::vector<int> GetValuesOfVariable(const std::string variable);

		void LoadPaddingData();
		void LoadLineSizes();
		void LoadCharacterData(int imageWidth);
		Character LoadCharacter(int imageSize);

	};
}

#endif