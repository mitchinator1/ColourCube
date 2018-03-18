#pragma once
#include <string>
#include <iostream>

#include "Character.h"
#include "TextMeshCreator.h"

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

	Map<Integer, Character> metaData = new HashMap<Integer, Character>();

	BufferedReader m_Reader;
	Map<String, String> values = new HashMap<String, String>();


public:
	MetaFile(File file)
	{
		m_AspectRatio = (double)Display.GetWidth() / (double)Display.GetHeight();
		OpenFile(file);
		LoadPaddingData();
		LoadLineSizes();
		int imageWidth = GetValueOfVariable("scaleW");
		LoadCharacterData(imageWidth);
		Close();
	}

	float GetSpaceWidth()
	{
		return m_SpaceWidth;
	}

	Character& GetCharacter(int ascii)
	{
		return m_MetaData.get(ascii);
	}

private:
	bool ProcessNextLine()
	{
		values.clear();
		std::string line;
		try
		{
			line = m_Reader.readLine();
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
				values.put(valuePairs[0], valuePairs[1]);
			}
		}
		return true;
	}

	int GetValueOfVariable(const std::string& variable)
	{
		return Integer.parseInt(values.get(variable));
	}

	std::vector<int> GetValuesOfVariable(const std::string variable)
	{
		std::string[] numbers = values.get(variable).split(NUMBER_SEPARATOR);
		std::vector<int> actualValues;
		actualValues.resize(numbers.size());
		for (int i = 0; i < actualValues.size(); ++i) {
			actualValues[i] = Integer.parseInt(numbers[i]);
		}
		return actualValues;
	}

	void Close()
	{
		try
		{
			m_Reader.close();
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}
	}

	void OpenFile(File file)
	{
		try
		{
			m_Reader = new BufferedReader(new FileReader(file));
		}
		catch (Exception e)
		{
			e.printStackTrace();
			std::cout << "Couldn't read font meta file!" << std::endl;
		}
	}

	void LoadPaddingData()
	{
		ProcessNextLine();
		m_Padding = GetValuesOfVariable("padding");
		m_PaddingWidth = m_Padding[PAD_LEFT] + m_Padding[PAD_RIGHT];
		m_PaddingHeight = m_Padding[PAD_TOP] + m_Padding[PAD_BOTTOM];
	}

	void LoadLineSizes()
	{
		ProcessNextLine();
		int lineHeightPixels = GetValueOfVariable("lineHeight") - m_PaddingHeight;
		m_VerticalPerPixelSize = TextMeshCreator.LINE_HEIGHT / (float)lineHeightPixels;
		m_HorizontalPerPixelSize = m_VerticalPerPixelSize / m_AspectRatio;
	}

	void loadCharacterData(int imageWidth)
	{
		ProcessNextLine();
		ProcessNextLine();
		while (ProcessNextLine())
		{
			Character c = LoadCharacter(imageWidth);
			if (c != null)
			{
				metaData.put(c.getId(), c);
			}
		}
	}

	Character* LoadCharacter(int imageSize)
	{
		int id = GetValueOfVariable("id");
		if (id == TextMeshCreator.SPACE_ASCII)
		{
			m_SpaceWidth = (GetValueOfVariable("xadvance") - m_PaddingWidth) * m_HorizontalPerPixelSize;
			return nullptr;
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

};