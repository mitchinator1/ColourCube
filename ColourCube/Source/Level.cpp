#include "Level.h"
#include "Mesh/VertexBufferLayout.h"
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

Level::Level()
	: m_Position({ 0.0f, 0.0f, 0.0f }), m_Input(nullptr), m_Count(0), m_CurrentLevel(0)
{

}

Level::Level(Input::InputBase* input)
	: m_Position({ 0.0f, 0.0f, 0.0f }), m_Input(input), m_Count(0), m_CurrentLevel(0)
{
	LoadLevel("Level.data");
	std::cout << "Level " << m_CurrentLevel << " loaded." << std::endl;
	CalculatePosition();
	std::cout << "Level position: [" << m_Position.x << "][" << m_Position.y << "][" << m_Position.z << "]" << std::endl;
}

Level::~Level()
{
	delete m_Input;
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
	PrepareVertices(m_Cubes);

	Bind();

	VertexBuffer vb(m_Vertices);
	IndexBuffer ib(GetIndices());

	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(3);
	layout.Push<float>(3);
	m_VA.AddBuffer(vb, layout);

	Unbind();
}

void Level::HandleEvents()
{
	m_Input->HandleEvents();
}

void Level::Update()
{
	m_Input->Update(*this);

	if (m_Updated)
	{
		PrepareVertices(m_Cubes);
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
		ChangeColour(0, 0, 0, Face::NORTH);
		//ChangeColour((int)UpdateCoords.x, (int)UpdateCoords.y, (int)UpdateCoords.z, BOTTOM);
		break;
	case Command::CHANGE_COLOUR_2: // Test Colour Change
		ChangeColour(1, 0, 1, Face::EAST);
		break;
	}
}

void Level::Receive(glm::vec3 v)
{
	//TODO: fix
	glm::vec3 mouseRay = v;// +glm::vec3{ 5.0f, 5.0f, 5.0f };

	std::cout << mouseRay.x << ", " << mouseRay.y << ", " << mouseRay.z << std::endl;

	UpdateCoords = mouseRay;
}

void Level::Draw() const
{
	Bind();
	glDrawElements(GL_TRIANGLES, GetCount(), GL_UNSIGNED_INT, nullptr);
	Unbind();
}

void Level::Bind() const
{
	m_VA.Bind();
}

void Level::Unbind() const
{
	m_VA.Unbind();
}

std::vector<unsigned int> Level::GetIndices()
{
	std::vector<unsigned int> indices;

	for (unsigned int i = 0; i < m_Vertices.size() / 6; ++i)
		indices.insert(indices.end(), { i, ++i, ++i, i, ++i, i - 3 });

	m_Count = indices.size();

	return indices;
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

void Level::PrepareVertices(std::vector<Cube>& cubes)
{
	m_Vertices.clear();

	for (Cube& cube : cubes)
	{
		auto& vertices = cube.GetSides();
		m_Vertices.insert(m_Vertices.end(), vertices.begin(), vertices.end());
	}
}

void Level::UpdateVertices()
{
	Bind();
	glBufferSubData(GL_ARRAY_BUFFER, 0, m_Vertices.size() * sizeof(m_Vertices[0]), m_Vertices.data());
	Unbind();
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
	if (!CheckCubeFace(x, y, z, face))
	{
		std::cout << "Face doesn't exist at [" << x << "][" << y << "][" << z << "]!" << std::endl;
		return;
	}

	switch (face)
	{
	case Face::TOP: {
		if (!CheckCubeFace(x, y, z, Face::NORTH))
			if (!CheckCubeFace(x, y, z - 1, face))
				CheckCubeFace(x, y + 1, z - 1, Face::SOUTH);

		if (!CheckCubeFace(x, y, z, Face::EAST))
			if (!CheckCubeFace(x + 1, y, z, face))
				CheckCubeFace(x + 1, y + 1, z, Face::WEST);

		if (!CheckCubeFace(x, y, z, Face::SOUTH))
			if (!CheckCubeFace(x, y, z + 1, face))
				CheckCubeFace(x, y + 1, z + 1, Face::NORTH);

		if (!CheckCubeFace(x, y, z, Face::WEST))
			if (!CheckCubeFace(x - 1, y, z, face))
				CheckCubeFace(x - 1, y + 1, z, Face::EAST);
	}
		break;
	case Face::NORTH: {
		if (!CheckCubeFace(x, y, z, Face::TOP))
			if (!CheckCubeFace(x, y + 1, z, face))
				CheckCubeFace(x, y + 1, z - 1, Face::BOTTOM);

		if (!CheckCubeFace(x, y, z, Face::BOTTOM))
			if (!CheckCubeFace(x, y - 1, z, face))
				CheckCubeFace(x, y - 1, z - 1, Face::TOP);

		if (!CheckCubeFace(x, y, z, Face::WEST))
			if (!CheckCubeFace(x - 1, y, z, face))
				CheckCubeFace(x - 1, y, z - 1, Face::EAST);

		if (!CheckCubeFace(x, y, z, Face::EAST))
			if (!CheckCubeFace(x + 1, y, z, face))
				CheckCubeFace(x + 1, y, z - 1, Face::EAST);
	}
		break;
	case Face::EAST: { 
		if (!CheckCubeFace(x, y, z, Face::TOP))
			if (!CheckCubeFace(x, y + 1, z, face))
				CheckCubeFace(x + 1, y + 1, z, Face::BOTTOM);

		if (!CheckCubeFace(x, y, z, Face::BOTTOM))
			if (!CheckCubeFace(x, y - 1, z, face))
				CheckCubeFace(x + 1, y - 1, z, Face::TOP);

		if (!CheckCubeFace(x, y, z, Face::NORTH))
			if (!CheckCubeFace(x, y, z - 1, face))
				CheckCubeFace(x + 1, y, z - 1, Face::SOUTH);

		if (!CheckCubeFace(x, y, z, Face::SOUTH))
			if (!CheckCubeFace(x, y, z + 1, face))
				CheckCubeFace(x + 1, y, z + 1, Face::NORTH);
	}
		break;
	case Face::SOUTH: {
		if (!CheckCubeFace(x, y, z, Face::TOP))
			if (!CheckCubeFace(x, y + 1, z, face))
				CheckCubeFace(x, y + 1, z + 1, Face::BOTTOM);

		if (!CheckCubeFace(x, y, z, Face::BOTTOM))
			if (!CheckCubeFace(x, y - 1, z, face))
				CheckCubeFace(x, y - 1, z + 1, Face::TOP);

		if (!CheckCubeFace(x, y, z, Face::WEST))
			if (!CheckCubeFace(x - 1, y, z, face))
				CheckCubeFace(x - 1, y, z + 1, Face::EAST);

		if (!CheckCubeFace(x, y, z, Face::EAST))
			if (!CheckCubeFace(x + 1, y, z, face))
				CheckCubeFace(x - 1, y, z - 1, Face::WEST);
	}
		break;
	case Face::WEST: {
		if (!CheckCubeFace(x, y, z, Face::TOP))
			if (!CheckCubeFace(x, y + 1, z, face))
				CheckCubeFace(x - 1, y + 1, z, Face::BOTTOM);

		if (!CheckCubeFace(x, y, z, Face::BOTTOM))
			if (!CheckCubeFace(x, y - 1, z, face))
				CheckCubeFace(x - 1, y - 1, z, Face::TOP);

		if (!CheckCubeFace(x, y, z, Face::NORTH))
			if (!CheckCubeFace(x, y, z - 1, face))
				CheckCubeFace(x - 1, y, z - 1, Face::SOUTH);

		if (!CheckCubeFace(x, y, z, Face::SOUTH))
			if (!CheckCubeFace(x, y, z + 1, face))
				CheckCubeFace(x - 1, y, z - 1, Face::NORTH);
	}
		break;
	case Face::BOTTOM: {
		if (!CheckCubeFace(x, y, z, Face::NORTH))
			if (!CheckCubeFace(x, y, z - 1, face))
				CheckCubeFace(x, y - 1, z - 1, Face::SOUTH);

		if (!CheckCubeFace(x, y, z, Face::EAST))
			if (!CheckCubeFace(x + 1, y, z, face))
				CheckCubeFace(x + 1, y - 1, z, Face::WEST);
		
		if (!CheckCubeFace(x, y, z, Face::SOUTH))
			if (!CheckCubeFace(x, y, z + 1, face))
				CheckCubeFace(x, y - 1, z + 1, Face::NORTH);

		if (!CheckCubeFace(x, y, z, Face::WEST))
			if (!CheckCubeFace(x - 1, y, z, face))
				CheckCubeFace(x - 1, y - 1, z, Face::EAST);
	}
		break;
	default: std::cout << "Face doesn't exist" << std::endl;
		return;
	}

	m_Updated = true;
}

bool Level::CheckCubeFace(int x, int y, int z, Face face)
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
	for (unsigned int i = 0; i < m_Cubes.size() - 1; i++)
		if (m_Cubes[i] != m_Cubes[i + 1])
			return false;

	return true;
}