#include "LevelCreator.h"
#include "Cube.h"

LevelCreator::LevelCreator(const std::string& filename)
	:m_LevelNumber(0)
{
	LoadFile("Resources/Data/" + filename + ".xml");
}

LevelCreator::~LevelCreator()
{
	m_Stream.close();
}

void LevelCreator::LoadFile(const std::string& filepath)
{
	m_Stream.open(filepath);
	if (!m_Stream.good())
	{
		m_Stream.open("Resources/Data/LevelTemplate.xml");
	}

	std::string line;

	while (std::getline(m_Stream, line, ' '))
	{
		if (line.find("Name") != std::string::npos)
		{
			//Save level name
			continue;
		}

		if (line.find("Colours") != std::string::npos)
		{
			GetRawColourData();
		}

		if (line.find("Cubes") != std::string::npos)
		{
			CreateCubes(GetRawCubeData());
		}
	}

}

std::vector<short> LevelCreator::GetRawCubeData()
{
	std::vector<short> cubes;

	std::string line;
	while (line != "/Cubes")
	{
		std::getline(m_Stream, line, '<');
		std::getline(m_Stream, line, '>');

		if (line == "position")
		{
			short i;
			while (m_Stream >> i)
				cubes.emplace_back(i);
			m_Stream.clear();
			continue;
		}

		if (line == "faces")
		{
			short i;
			while (m_Stream >> i)
				cubes.emplace_back(i);
			m_Stream.clear();
			continue;
		}

		if (line == "stage")
		{
			short i;
			while (m_Stream >> i)
				cubes.emplace_back(i);
			m_Stream.clear();
			continue;
		}

	}

	return cubes;
}

void LevelCreator::GetRawColourData()
{
	std::string line;
	while (line != "/Colours")
	{
		std::getline(m_Stream, line, '<');
		std::getline(m_Stream, line, '>');

		if (line == "colour")
		{
			glm::vec3 rgb;
			m_Stream >> rgb.r >> rgb.g >> rgb.b;
			m_PossibleColours.emplace_back(rgb);
		}
	}
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