#include "MetaFile.h"
#include <fstream>
#include <sstream>
#include <iostream>

namespace Text
{
	MetaFile::MetaFile(const std::string& filepath)
		: m_AspectRatio(1800.0f / 1200.0f)
	{
		//m_AspectRatio = (double)Display.GetWidth() / (double)Display.GetHeight();

		std::ifstream stream(filepath);
		if (!stream)
			std::cout << "Failed to open font meta file at : " << filepath << std::endl;

		std::string line;
		int imageWidth;
		while (std::getline(stream, line))
		{
			if (line.find("info") != std::string::npos)
			{
				std::istringstream parts(line);
				std::string title;
				std::getline(parts, title, ' ');
				InsertValues(parts);
				LoadPaddingData();
				continue;
			}
			if (line.find("common") != std::string::npos)
			{
				std::istringstream parts(line);
				std::string title;
				std::getline(parts, title, ' ');
				InsertValues(parts);
				LoadLineSizes();
				imageWidth = GetValueOfVariable("scaleW");
				std::getline(stream, line);
				std::getline(stream, line);
				continue;
			}
			if (line.find("char") != std::string::npos)
			{
				m_Values.clear();
				std::istringstream parts(line);
				std::string title;
				std::getline(parts, title, ' ');
				InsertValues(parts);
				LoadCharacterData(imageWidth);
			}
		}

		stream.close();
	}

	MetaFile::~MetaFile()
	{

	}

	Character& MetaFile::GetCharacter(int ascii)
	{
		return m_MetaData[ascii];
	}

	void MetaFile::InsertValues(std::istringstream& iss)
	{
		while (iss)
		{
			std::string value1, value2;

			std::getline(iss, value1, '=');
			std::getline(iss, value2, ' ');

			TrimLeadingSpace(value1);
			TrimLeadingSpace(value2);

			m_Values.insert({ value1, value2 });
		}
	}

	void MetaFile::InsertChar(std::istringstream& iss)
	{
		m_Values.clear();
		std::string value1, value2;

		while (iss)
		{
			std::getline(iss, value1, '=');
			std::getline(iss, value2, ' ');
			m_Values.insert({ value1, value2 });
		}
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

	void MetaFile::TrimLeadingSpace(std::string& value, const char* t)
	{
		value.erase(0, value.find_first_not_of(t));
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