#include "MetaFile.h"
#include <fstream>

namespace Text
{
	MetaFile::MetaFile(const std::string& filepath)
	{
		m_AspectRatio = (double)Display.GetWidth() / (double)Display.GetHeight();
		OpenFile(filepath);
		LoadPaddingData();
		LoadLineSizes();
		int imageWidth = GetValueOfVariable("scaleW");
		LoadCharacterData(imageWidth);
		Close();
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
		try
		{
			//line = m_Reader.readLine();
		}
		catch (IOException e1)
		{

		}
		if (line == null)
		{
			return false;
		}
		for (auto& part : line.split(SPLITTER)) {
			String[] valuePairs = part.split("=");
			if (valuePairs.length == 2) {
				m_Values.insert({ valuePairs[0], valuePairs[1] });
			}
		}
		return true;
	}

	int MetaFile::GetValueOfVariable(const std::string& variable)
	{
		return Integer.parseInt(m_Values.find(variable));
	}

	std::vector<int> MetaFile::GetValuesOfVariable(const std::string variable)
	{
		std::string[] numbers = values.get(variable).split(NUMBER_SEPARATOR);
		std::vector<int> actualValues;
		actualValues.resize(numbers.size());
		for (int i = 0; i < actualValues.size(); ++i) {
			actualValues[i] = Integer.parseInt(numbers[i]);
		}
		return actualValues;
	}

	void MetaFile::Close()
	{
		try
		{
			//m_Reader.close();
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}
	}

	void MetaFile::OpenFile(const std::string& filepath)
	{

		try
		{
			std::fstream m_Reader(filepath);
			//m_Reader = new BufferedReader(new FileReader(filepath));
		}
		catch (Exception e)
		{
			std::cout << "Couldn't read font meta file!" << std::endl;
		}
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

	void MetaFile::loadCharacterData(int imageWidth)
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