#pragma once
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

		const int DESIRED_PADDING = 3;

		const std::string SPLITTER = " ";
		const std::string NUMBER_SEPARATOR = ",";

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
		MetaFile(const std::string& filepath);

		float GetSpaceWidth();
		Character& GetCharacter(int ascii);

	private:
		bool ProcessNextLine();
		int GetValueOfVariable(const std::string& variable);
		std::vector<int> GetValuesOfVariable(const std::string variable);

		void Close();
		void OpenFile(const std::string& filepath);

		void LoadPaddingData();
		void LoadLineSizes();
		void loadCharacterData(int imageWidth);
		Character LoadCharacter(int imageSize);

	};
}