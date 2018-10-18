#include "MetaFile.h"
#include <fstream>

namespace Text
{
	MetaFile::MetaFile(const std::string& filepath, double width, double height) noexcept
		: m_AspectRatio(width / height), m_SpaceWidth(0)
		, m_VerticalPerPixelSize(0), m_HorizontalPerPixelSize(0)
		, m_PaddingWidth(0), m_PaddingHeight(0)
		, FileProgram(filepath)
	{
		LoadLine();
		LoadLine();
		LoadLine();
		LoadLine();

		LoadPaddingData();
		LoadLineSizes();
		int imageWidth = GetValueOfVariable("scaleW");
		ClearValueCache();

		while (LoadLine())
		{
			LoadCharacterData(imageWidth);
			ClearValueCache();
		}
	}

	MetaFile::~MetaFile()
	{

	}

	Character& MetaFile::GetCharacter(int ascii)
	{
		return m_MetaData[ascii];
	}

	int MetaFile::GetValueOfVariable(const std::string& variable)
	{
		std::string::size_type sz;
		return std::stoi(m_Values[variable], &sz);
	}

	std::vector<int> MetaFile::GetValuesOfVariable(const std::string variable)
	{
		std::string numbers = m_Values[variable];
		std::vector<int> actualValues;
		for (unsigned int i = 0; i < numbers.size(); i += 2)
		{
			int temp = numbers[i] - '0';
			actualValues.emplace_back(temp);
		}
		return actualValues;
	}
	
	void MetaFile::LoadPaddingData()
	{
		m_Padding = GetValuesOfVariable("padding");
		m_PaddingWidth = m_Padding[PAD_LEFT] + m_Padding[PAD_RIGHT];
		m_PaddingHeight = m_Padding[PAD_TOP] + m_Padding[PAD_BOTTOM];
	}

	void MetaFile::LoadLineSizes()
	{
		int lineHeightPixels = GetValueOfVariable("lineHeight") - m_PaddingHeight;
		m_VerticalPerPixelSize = LINE_HEIGHT / (float)lineHeightPixels;
		m_HorizontalPerPixelSize = m_VerticalPerPixelSize / (float)m_AspectRatio;
	}

	void MetaFile::LoadCharacterData(int imageWidth)
	{
		Character c = LoadCharacter(imageWidth);
		if (c.id != SPACE_ASCII)
			m_MetaData.insert({ c.id, c });
	}

	Character MetaFile::LoadCharacter(int imageSize)
	{
		int id = GetValueOfVariable("id");
		if (id == SPACE_ASCII)
			m_SpaceWidth = (GetValueOfVariable("xadvance") - m_PaddingWidth) * m_HorizontalPerPixelSize;

		float xTex = ((float)GetValueOfVariable("x") + (m_Padding[PAD_LEFT] - DESIRED_PADDING)) / imageSize;
		float yTex = ((float)GetValueOfVariable("y") + (m_Padding[PAD_TOP] - DESIRED_PADDING)) / imageSize;
		int width = GetValueOfVariable("width") - (m_PaddingWidth - (2 * DESIRED_PADDING));
		int height = GetValueOfVariable("height") - (m_PaddingHeight - (2 * DESIRED_PADDING));
		float xTexSize = (float)width / (float)imageSize;
		float yTexSize = (float)height / (float)imageSize;
		float quadWidth = width * m_HorizontalPerPixelSize;
		float quadHeight = height * m_VerticalPerPixelSize;
		float xOff = (GetValueOfVariable("xoffset") + m_Padding[PAD_LEFT] - DESIRED_PADDING) * m_HorizontalPerPixelSize;
		float yOff = (GetValueOfVariable("yoffset") + (m_Padding[PAD_TOP] - DESIRED_PADDING)) * m_VerticalPerPixelSize;
		float xAdvance = (GetValueOfVariable("xadvance") - m_PaddingWidth) * m_HorizontalPerPixelSize;

		return Character(id, xTex, 1.0f - yTex, xTexSize, yTexSize, xOff, yOff, quadWidth, quadHeight, xAdvance);
	}
}