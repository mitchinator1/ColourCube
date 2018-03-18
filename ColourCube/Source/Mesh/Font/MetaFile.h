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
	int[] padding;
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
		return metaData.get(ascii);
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

	int/*[]*/ GetValuesOfVariable(const std::string variable)
	{
		std::string[] numbers = values.get(variable).split(NUMBER_SEPARATOR);
		int[] actualValues = new int[numbers.length];
		for (int i = 0; i < actualValues.length; i++) {
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
		padding = GetValuesOfVariable("padding");
		m_PaddingWidth = padding[PAD_LEFT] + padding[PAD_RIGHT];
		m_PaddingHeight = padding[PAD_TOP] + padding[PAD_BOTTOM];
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

		float xTex = ((float)GetValueOfVariable("x") + (padding[PAD_LEFT] - DESIRED_PADDING)) / imageSize;
		float yTex = ((float)GetValueOfVariable("y") + (padding[PAD_TOP] - DESIRED_PADDING)) / imageSize;
		int width = GetValueOfVariable("width") - (m_PaddingWidth - (2 * DESIRED_PADDING));
		int height = GetValueOfVariable("height") - ((m_PaddingHeight)-(2 * DESIRED_PADDING));
		float quadWidth = width * m_HorizontalPerPixelSize;
		float quadHeight = height * m_VerticalPerPixelSize;
		float xTexSize = (double)width / imageSize;
		float yTexSize = (double)height / imageSize;
		float xOff = (GetValueOfVariable("xoffset") + padding[PAD_LEFT] - DESIRED_PADDING) * m_HorizontalPerPixelSize;
		float yOff = (GetValueOfVariable("yoffset") + (padding[PAD_TOP] - DESIRED_PADDING)) * m_VerticalPerPixelSize;
		float xAdvance = (GetValueOfVariable("xadvance") - m_PaddingWidth) * m_HorizontalPerPixelSize;

		return Character(id, xTex, yTex, xTexSize, yTexSize, xOff, yOff, quadWidth, quadHeight, xAdvance);
	}

};