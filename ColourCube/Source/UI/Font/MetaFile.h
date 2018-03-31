#ifndef META_FILE_H
#define META_FILE_H
#include <string>
#include <iostream>
#include <unordered_map>

#include "Character.h"
#include "TextMeshCreator.h"

namespace Text
{
	class MetaFile {
	private:
		const int PAD_TOP = 0;
		const int PAD_LEFT = 1;
		const int PAD_BOTTOM = 2;
		const int PAD_RIGHT = 3;
		const int DESIRED_PADDING = 8;

		double m_AspectRatio;

		float m_VerticalPerPixelSize;
		float m_HorizontalPerPixelSize;
		float m_SpaceWidth;
		std::vector<int> m_Padding;
		int m_PaddingWidth;
		int m_PaddingHeight;

		std::unordered_map<int, Character> m_MetaData;
		std::unordered_map<std::string, std::string> m_Values;

	public:
		MetaFile(const std::string& filepath = "Resources/Font/Arial.fnt");

		float GetSpaceWidth() { return m_SpaceWidth; }
		Character& GetCharacter(int ascii);

	private:
		void InsertValues(std::istringstream& iss);
		void InsertChar(std::istringstream& iss);
		int GetValueOfVariable(const std::string& variable);
		std::vector<int> GetValuesOfVariable(const std::string variable);

		void TrimLeadingSpace(std::string& value, const char* t = " \t\n\r\f\v");

		void LoadPaddingData();
		void LoadLineSizes();
		void LoadCharacterData(int imageWidth);
		Character LoadCharacter(int imageSize);

	};
}

#endif