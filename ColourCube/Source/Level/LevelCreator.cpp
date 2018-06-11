#include "LevelCreator.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "Cube.h"

LevelCreator::LevelCreator(const std::string& filename)
	:m_LevelNumber(0)
{
	LoadFile("Resources/Data/" + filename);
}

LevelCreator::~LevelCreator()
{

}

void LevelCreator::LoadFile(const std::string& filepath)
{
	enum class DataType { LEVEL = 0, ROWS = 1, POSSIBLE_COLOURS = 2, CUBES = 3 };

	std::ifstream stream(filepath);
	if (!stream.good())
	{
		stream.open("Resources/Data/BlankLevel.data");
	}

	unsigned int i;
	std::string line;
	DataType type = DataType::LEVEL;
	std::vector<int> cubes;

	while (std::getline(stream, line))
	{
		if (line.empty()) continue;

		if (line.find("#level") != std::string::npos)
		{
			type = DataType::LEVEL;
			continue;
		}
		else if (line.find("#possible_colours") != std::string::npos)
		{
			type = DataType::POSSIBLE_COLOURS;
			continue;
		}
		else if (line.find("#cubes") != std::string::npos)
		{
			type = DataType::CUBES;
			continue;
		}

		std::stringstream ss(line);

		switch (type)
		{
		case DataType::LEVEL: {
			ss >> m_LevelNumber;
		}
			break;
		case DataType::POSSIBLE_COLOURS: {
			std::vector<float> rgb;
			float i;
			while (ss >> i)
				rgb.emplace_back(i);
			m_PossibleColours.emplace_back(rgb[0], rgb[1], rgb[2]);
		}
			break;
		case DataType::CUBES: {
			while (ss >> i)
				cubes.emplace_back(i);
		}
			break;
		}
	}

	CreateCubes(cubes);
}

std::vector<float> LevelCreator::GetVertices()
{
	std::vector<float> vertices;
	for (auto& cube : m_Cubes)
	{
		auto& cubeVertices = cube.GetVertices();
		vertices.insert(vertices.end(), cubeVertices.begin(), cubeVertices.end());
	}
	return vertices;
}

void LevelCreator::CreateCubes(const std::vector<int>& data)
{
	for (unsigned int i = 0; i < data.size(); i += 15)
	{
		glm::vec3 position = { data[i], data[i + 1], data[i + 2] };
		std::vector<Side> sides;
		if (data[i + 3])
			sides.emplace_back(Side{ Face::TOP, data.at(i + 9) });
		if (data[i + 4])
			sides.emplace_back(Side{ Face::NORTH, data.at(i + 10) });
		if (data[i + 5])
			sides.emplace_back(Side{ Face::EAST, data.at(i + 11) });
		if (data[i + 6])
			sides.emplace_back(Side{ Face::SOUTH, data.at(i + 12) });
		if (data[i + 7])
			sides.emplace_back(Side{ Face::WEST, data.at(i + 13) });
		if (data[i + 8])
			sides.emplace_back(Side{ Face::BOTTOM, data.at(i + 14) });

		m_Cubes.emplace_back(sides, m_PossibleColours, position.x, position.y, position.z);

		if (m_Position.x < position.x)
			m_Position.x = position.x;
		if (m_Position.y < position.y)
			m_Position.y = position.y;
		if (m_Position.z < position.z)
			m_Position.z = position.z;
	}
}