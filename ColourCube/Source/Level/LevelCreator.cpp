#include "LevelCreator.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "Cube.h"

LevelCreator::LevelCreator(const std::string& filename)
	:m_LevelNumber(0)
{
	LoadFile("Resources/Data/" + filename + ".data");
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

	unsigned short i;
	std::string line;
	DataType type = DataType::LEVEL;
	std::vector<short> cubes;

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
			m_PossibleColours.emplace_back(glm::vec3{ rgb[0], rgb[1], rgb[2] });
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
		auto& cubeVertices = cube->GetVertices();
		vertices.insert(vertices.end(), cubeVertices.begin(), cubeVertices.end());
	}
	return vertices;
}

void LevelCreator::CreateCubes(const std::vector<short>& data)
{
	float minX = 0.0f, maxX = 0.0f, minY = 0.0f, maxY = 0.0f, minZ = 0.0f, maxZ = 0.0f;

	for (short i = 0; i < (short)data.size(); i += 15)
	{
		glm::vec3 position = { data[i], data[i + 1], data[i + 2] };
		std::unordered_map<Face, short> sides;
		if (data[i + 3])
			sides.insert({ Face::TOP, data.at(i + 9) });
		if (data[i + 4])
			sides.insert({ Face::NORTH, data.at(i + 10) });
		if (data[i + 5])
			sides.insert({ Face::EAST, data.at(i + 11) });
		if (data[i + 6])
			sides.insert({ Face::SOUTH, data.at(i + 12) });
		if (data[i + 7])
			sides.insert({ Face::WEST, data.at(i + 13) });
		if (data[i + 8])
			sides.insert({ Face::BOTTOM, data.at(i + 14) });

		m_Cubes.emplace_back(std::make_unique<Cube>(sides, m_PossibleColours, position.x, position.y, position.z));

		if (position.x < minX)		minX = position.x;
		if (position.y < minY)		minY = position.y;
		if (position.z < minZ)		minZ = position.z;
		if (position.x > maxX)		maxX = position.x;
		if (position.y > maxY)		maxY = position.y;
		if (position.z > maxZ)		maxZ = position.z;
	}

	float x = (minX + maxX) / 2.0f;
	float y = (minY + maxY) / 2.0f;
	float z = (minZ + maxZ) / 2.0f;
	m_Position = { x, y, z };

}