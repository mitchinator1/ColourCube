#include "Level.h"
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

Level::Level()
	: m_Position({ 0.0f, 0.0f, 0.0f }), m_Mesh(nullptr), m_Input(nullptr), m_CurrentLevel(0)
{

}

Level::Level(std::unique_ptr<Input::InputBase> input)
	: m_Position({ 0.0f, 0.0f, 0.0f }), m_Mesh(nullptr), m_Input(std::move(input)), m_CurrentLevel(0)
{
	LoadLevel("Level.data");
	std::cout << "Level " << m_CurrentLevel << " loaded." << std::endl;
	CalculatePosition();
	std::cout << "Level position: [" << m_Position.x << "][" << m_Position.y << "][" << m_Position.z << "]" << std::endl;
}

Level::~Level()
{
	delete m_Mesh;
}

void Level::LoadLevel(const std::string& filepath)
{
	enum class DataType { LEVEL = 0, ROWS = 1, POSSIBLE_COLOURS = 2, CUBES = 3 };
	std::ifstream stream("Resources/Data/" + filepath);
	unsigned int i;
	std::string line;
	DataType type = DataType::LEVEL;
	std::vector<int> cubes;

	while (getline(stream, line))
	{
		if (line.empty()) continue;

		if (line.find("#level") != std::string::npos)
		{
			type = DataType::LEVEL;
			continue;
		}
		else if (line.find("#rows") != std::string::npos)
		{
			type = DataType::ROWS;
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
				ss >> m_CurrentLevel;
			}
			break;
		case DataType::ROWS: {
				std::vector<unsigned int> row;
				while (ss >> i)
					row.emplace_back(i);
				m_CubeKey.emplace_back(row);
			}
			break;
		case DataType::POSSIBLE_COLOURS: {
				std::vector<float> rgb;
				float i;
				while (ss >> i)
					rgb.emplace_back(i);
				m_PossibleColours.emplace_back(Colour{ rgb[0], rgb[1], rgb[2] });
			}
			break;
		case DataType::CUBES: {
				while (ss >> i)
					cubes.emplace_back(i);
			}
			break;
		}
 	}

	CreateLevel(cubes);
}

void Level::CreateLevel(const std::vector<int>& data)
{
	PrepareCubes(data);

	std::vector<float> vertices;
	for (Cube& cube : m_Cubes)
	{
		auto& cubeVertices = cube.GetSides();
		vertices.insert(vertices.end(), cubeVertices.begin(), cubeVertices.end());
	}

	m_Mesh = new Mesh(vertices, 3, 3);
}

void Level::HandleEvents()
{
	m_Input->HandleEvents(*this);
}

void Level::Update()
{
	m_Input->Update(*this);

	if (m_Updated)
	{
		UpdateVertices();

		if (CheckWin())
			std::cout << "Win!" << std::endl;

		m_Updated = false;
	}
}

void Level::Action(Command command)
{
	switch (command)
	{
	case Command::CHANGE_COLOUR:
		//ChangeColour(0, 0, 1, Face::BOTTOM);
		ChangeColour((int)UpdateCoords.x, (int)UpdateCoords.y, (int)UpdateCoords.z, Face::BOTTOM);
		break;
	case Command::CHANGE_COLOUR_2: // Test Colour Change
		ChangeColour(1, 0, 1, Face::EAST);
		break;
	}
}

//TODO: fix
void Level::Receive(glm::vec3 v)
{
	glm::vec3 mouseRay = v;

	glm::vec3 pickedCube = { 4.0f, 4.0f, 4.0f };

	int i = 0;
	while (i < 30)
	{
		for (unsigned int j = 0; j < m_Cubes.size(); ++j)
		{
			if (mouseRay.x == m_Cubes[j].GetPosition().x)
			{
				if (mouseRay.z == m_Cubes[j].GetPosition().z)
				{
					if (mouseRay.y == m_Cubes[j].GetPosition().y)
					{
						std::cout << "Cube: " << m_Cubes[j].GetPosition().x << ", " << m_Cubes[j].GetPosition().y << ", " << m_Cubes[j].GetPosition().z << std::endl;
						pickedCube = m_Cubes[j].GetPosition();
						break;
					}
				}
			}
		}
		mouseRay -= (v * 0.1f);
		++i;
	}

	std::cout << mouseRay.z << ", " << mouseRay.y << ", " << mouseRay.z << std::endl;

	UpdateCoords = pickedCube;
}

void Level::Draw() const
{
	Bind();
	glDrawElements(GL_TRIANGLES, m_Mesh->GetCount(), GL_UNSIGNED_INT, nullptr);
	Unbind();
}

void Level::Bind() const
{
	m_Mesh->Bind();
}

void Level::Unbind() const
{
	m_Mesh->Unbind();
}

void Level::PrepareCubes(const std::vector<int>& data)
{
	for (unsigned int i = 0; i < data.size(); i += 15)
	{
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

		m_Cubes.emplace_back(Cube(sides, &m_PossibleColours, (float)data[i], (float)data[i + 1], (float)data[i + 2]));
	}
}

void Level::UpdateVertices()
{
	std::vector<float> vertices;
	for (Cube& cube : m_Cubes)
	{
		auto& cubeVertices = cube.GetSides();
		vertices.insert(vertices.end(), cubeVertices.begin(), cubeVertices.end());
	}

	m_Mesh->UpdateVertices(vertices);
}

void Level::CalculatePosition()
{
	//TODO: Calculate based on average of all rows/columns
	m_Position.x = m_CubeKey[0][0] / 2.0f;
	m_Position.y = m_CubeKey.size() / 2.0f;
	m_Position.z = m_CubeKey[0].size() / 2.0f;
}

void Level::ChangeColour(int x, int y, int z, Face face)
{
	if (!CubeFaceExists(x, y, z, face))
	{
		std::cout << "Face doesn't exist at [" << x << "][" << y << "][" << z << "]!" << std::endl;
		return;
	}

	switch (face)
	{
	case Face::TOP: {
		if (!CubeFaceExists(x, y, z, Face::NORTH))
			if (!CubeFaceExists(x, y, z - 1, face))
				CubeFaceExists(x, y + 1, z - 1, Face::SOUTH);

		if (!CubeFaceExists(x, y, z, Face::EAST))
			if (!CubeFaceExists(x + 1, y, z, face))
				CubeFaceExists(x + 1, y + 1, z, Face::WEST);

		if (!CubeFaceExists(x, y, z, Face::SOUTH))
			if (!CubeFaceExists(x, y, z + 1, face))
				CubeFaceExists(x, y + 1, z + 1, Face::NORTH);

		if (!CubeFaceExists(x, y, z, Face::WEST))
			if (!CubeFaceExists(x - 1, y, z, face))
				CubeFaceExists(x - 1, y + 1, z, Face::EAST);
	}
		break;
	case Face::NORTH: {
		if (!CubeFaceExists(x, y, z, Face::TOP))
			if (!CubeFaceExists(x, y + 1, z, face))
				CubeFaceExists(x, y + 1, z - 1, Face::BOTTOM);

		if (!CubeFaceExists(x, y, z, Face::BOTTOM))
			if (!CubeFaceExists(x, y - 1, z, face))
				CubeFaceExists(x, y - 1, z - 1, Face::TOP);

		if (!CubeFaceExists(x, y, z, Face::WEST))
			if (!CubeFaceExists(x - 1, y, z, face))
				CubeFaceExists(x - 1, y, z - 1, Face::EAST);

		if (!CubeFaceExists(x, y, z, Face::EAST))
			if (!CubeFaceExists(x + 1, y, z, face))
				CubeFaceExists(x + 1, y, z - 1, Face::EAST);
	}
		break;
	case Face::EAST: { 
		if (!CubeFaceExists(x, y, z, Face::TOP))
			if (!CubeFaceExists(x, y + 1, z, face))
				CubeFaceExists(x + 1, y + 1, z, Face::BOTTOM);

		if (!CubeFaceExists(x, y, z, Face::BOTTOM))
			if (!CubeFaceExists(x, y - 1, z, face))
				CubeFaceExists(x + 1, y - 1, z, Face::TOP);

		if (!CubeFaceExists(x, y, z, Face::NORTH))
			if (!CubeFaceExists(x, y, z - 1, face))
				CubeFaceExists(x + 1, y, z - 1, Face::SOUTH);

		if (!CubeFaceExists(x, y, z, Face::SOUTH))
			if (!CubeFaceExists(x, y, z + 1, face))
				CubeFaceExists(x + 1, y, z + 1, Face::NORTH);
	}
		break;
	case Face::SOUTH: {
		if (!CubeFaceExists(x, y, z, Face::TOP))
			if (!CubeFaceExists(x, y + 1, z, face))
				CubeFaceExists(x, y + 1, z + 1, Face::BOTTOM);

		if (!CubeFaceExists(x, y, z, Face::BOTTOM))
			if (!CubeFaceExists(x, y - 1, z, face))
				CubeFaceExists(x, y - 1, z + 1, Face::TOP);

		if (!CubeFaceExists(x, y, z, Face::WEST))
			if (!CubeFaceExists(x - 1, y, z, face))
				CubeFaceExists(x - 1, y, z + 1, Face::EAST);

		if (!CubeFaceExists(x, y, z, Face::EAST))
			if (!CubeFaceExists(x + 1, y, z, face))
				CubeFaceExists(x - 1, y, z - 1, Face::WEST);
	}
		break;
	case Face::WEST: {
		if (!CubeFaceExists(x, y, z, Face::TOP))
			if (!CubeFaceExists(x, y + 1, z, face))
				CubeFaceExists(x - 1, y + 1, z, Face::BOTTOM);

		if (!CubeFaceExists(x, y, z, Face::BOTTOM))
			if (!CubeFaceExists(x, y - 1, z, face))
				CubeFaceExists(x - 1, y - 1, z, Face::TOP);

		if (!CubeFaceExists(x, y, z, Face::NORTH))
			if (!CubeFaceExists(x, y, z - 1, face))
				CubeFaceExists(x - 1, y, z - 1, Face::SOUTH);

		if (!CubeFaceExists(x, y, z, Face::SOUTH))
			if (!CubeFaceExists(x, y, z + 1, face))
				CubeFaceExists(x - 1, y, z - 1, Face::NORTH);
	}
		break;
	case Face::BOTTOM: {
		if (!CubeFaceExists(x, y, z, Face::NORTH))
			if (!CubeFaceExists(x, y, z - 1, face))
				CubeFaceExists(x, y - 1, z - 1, Face::SOUTH);

		if (!CubeFaceExists(x, y, z, Face::EAST))
			if (!CubeFaceExists(x + 1, y, z, face))
				CubeFaceExists(x + 1, y - 1, z, Face::WEST);
		
		if (!CubeFaceExists(x, y, z, Face::SOUTH))
			if (!CubeFaceExists(x, y, z + 1, face))
				CubeFaceExists(x, y - 1, z + 1, Face::NORTH);

		if (!CubeFaceExists(x, y, z, Face::WEST))
			if (!CubeFaceExists(x - 1, y, z, face))
				CubeFaceExists(x - 1, y - 1, z, Face::EAST);
	}
		break;
	default: std::cout << "Face doesn't exist" << std::endl;
		return;
	}

	m_Updated = true;
}

bool Level::CubeFaceExists(int x, int y, int z, Face face)
{	
	if (x < 0 || y < 0 || z < 0)
		return false;

	if ((unsigned int)y >= m_CubeKey.size() || (unsigned int)z >= m_CubeKey[y].size() || (unsigned int)x > m_CubeKey[y][z])
	{
		std::cout << m_CubeKey[y].size() << std::endl;
		return false;
	}
	
	int index = 0;
	for (int i = 0; i < y; i++)
		for (unsigned int j = 0; j < m_CubeKey[i].size(); j++)
			index += m_CubeKey[i][j];

	index += (z * m_CubeKey[y].size()) + x;

	if (m_Cubes[index].CheckFace(face))
		m_Cubes[index].ChangeColour(face);
	else
		return false;

	return true;
}

bool Level::CheckWin()
{
	for (unsigned int i = 0; i < m_Cubes.size() - 1; ++i)
		if (m_Cubes[i] != m_Cubes[i + 1])
			return false;

	return true;
}