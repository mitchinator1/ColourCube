#include "MetaFile.h"
#include <fstream>

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
		while (std::getline(stream, line))
		{
			if (line.find("info ") != std::string::npos)
			{
				std::string value1;
				std::string value2;
				getline(stream, value1, '=');
				getline(stream, value2, ' ');
				m_Values.insert({ value1, value2 });
			}
		}

		LoadPaddingData();
		LoadLineSizes();
		int imageWidth = GetValueOfVariable("scaleW");
		LoadCharacterData(imageWidth);

		stream.close();
	}

	float MetaFile::GetSpaceWidth()
	{
		return m_SpaceWidth;
	}

	Character& MetaFile::GetCharacter(int ascii)
	{
		return m_MetaData[ascii];
	}

	bool MetaFile::ProcessNextLine()
	{
		//TODO: Read file
		m_Values.clear();
		std::string line;

		//line = m_Reader.readLine();

		if (line.empty())
		{
			return false;
		}
		for (auto& part : line.split(SPLITTER))
		{
			std::string valuePairs = part.split("=");
			if (valuePairs.length == 2)
			{
				m_Values.insert({ valuePairs[0], valuePairs[1] });
			}
		}
		return true;
	}

	int MetaFile::GetValueOfVariable(const std::string& variable)
	{
		return std::stoi(m_Values[variable]);
	}

	std::vector<int> MetaFile::GetValuesOfVariable(const std::string variable)
	{
		//std::string[] numbers = m_Values.get(variable).split(NUMBER_SEPARATOR);
		std::string numbers = m_Values[variable];
		std::vector<int> actualValues;
		for (int i = 0; i < actualValues.size(); ++i)
		{
			actualValues.emplace_back(numbers[i]);
		}
		return actualValues;
	}

	void MetaFile::LoadPaddingData()
	{
		ProcessNextLine();
		m_Padding = GetValuesOfVariable("padding");
		m_PaddingWidth = m_Padding[PAD_LEFT] + m_Padding[PAD_RIGHT];
		m_PaddingHeight = m_Padding[PAD_TOP] + m_Padding[PAD_BOTTOM];
	}

	void MetaFile::LoadLineSizes()
	{
		ProcessNextLine();
		int lineHeightPixels = GetValueOfVariable("lineHeight") - m_PaddingHeight;
		m_VerticalPerPixelSize = TextMeshCreator::LINE_HEIGHT / (float)lineHeightPixels;
		m_HorizontalPerPixelSize = m_VerticalPerPixelSize / m_AspectRatio;
	}

	void MetaFile::LoadCharacterData(int imageWidth)
	{
		ProcessNextLine();
		ProcessNextLine();
		while (ProcessNextLine())
		{
			Character c = LoadCharacter(imageWidth);
			//if (c != 0)
			//{
				m_MetaData.insert({ c.id, c });
			//}
		}
	}

	Character MetaFile::LoadCharacter(int imageSize)
	{
		int id = GetValueOfVariable("id");
		if (id == TextMeshCreator::SPACE_ASCII)
		{
			m_SpaceWidth = (GetValueOfVariable("xadvance") - m_PaddingWidth) * m_HorizontalPerPixelSize;
			return;
		}

		float xTex = ((float)GetValueOfVariable("x") + (m_Padding[PAD_LEFT] - DESIRED_PADDING)) / imageSize;
		float yTex = ((float)GetValueOfVariable("y") + (m_Padding[PAD_TOP] - DESIRED_PADDING)) / imageSize;
		int width = GetValueOfVariable("width") - (m_PaddingWidth - (2 * DESIRED_PADDING));
		int height = GetValueOfVariable("height") - ((m_PaddingHeight)-(2 * DESIRED_PADDING));
		float quadWidth = width * m_HorizontalPerPixelSize;
		float quadHeight = height * m_VerticalPerPixelSize;
		float xTexSize = (double)width / imageSize;
		float yTexSize = (double)height / imageSize;
		float xOff = (GetValueOfVariable("xoffset") + m_Padding[PAD_LEFT] - DESIRED_PADDING) * m_HorizontalPerPixelSize;
		float yOff = (GetValueOfVariable("yoffset") + (m_Padding[PAD_TOP] - DESIRED_PADDING)) * m_VerticalPerPixelSize;
		float xAdvance = (GetValueOfVariable("xadvance") - m_PaddingWidth) * m_HorizontalPerPixelSize;

		return Character(id, xTex, yTex, xTexSize, yTexSize, xOff, yOff, quadWidth, quadHeight, xAdvance);
	}
}