#include "Grid.h"
#include "VertexBufferLayout.h"
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

Grid::Grid()
	: m_Position({0.0f, 0.0f, 0.0f}), m_Input(nullptr), m_Count(0)
{
	
}

Grid::Grid(BasicInput* input)
	: m_Position({ 0.0f, 0.0f, 0.0f }), m_Input(input), m_Count(0), m_CurrentLevel(0)
{
	LoadLevel("Resources/Data/levels.data");
	std::cout << "Level " << m_CurrentLevel << " loaded." << std::endl;
}

Grid::~Grid()
{
	delete m_Input;
}

void Grid::LoadLevel(const std::string& filepath)
{
	std::ifstream stream(filepath);
	std::vector<std::vector<std::vector<unsigned int>>> level;
	std::vector<unsigned int> row;
	std::vector<std::vector<unsigned int>> column;
	unsigned int i;
	std::string line;
	while (stream >> line)
	{
		if (line.find("#level") != std::string::npos)
		{
			stream >> m_CurrentLevel;
		}
		while (stream >> i)
		{
			row.emplace_back(i);

			if (stream.peek() == '\n')
			{
				column.emplace_back(row);
				row.clear();
				stream >> line;
				if (line.find("#layer") != std::string::npos)
				{
					level.emplace_back(column);
					column.clear();
				}
			}
		}
		level.emplace_back(column);
	}
	CreateLevel(level);
}

void Grid::CreateLevel(const std::vector<std::vector<std::vector<unsigned int>>>& map)
{
	PrepareCubes(map);
	PrepareVertices(m_Cubes);

	Bind();

	VertexBuffer vb(m_Vertices);
	IndexBuffer ib(GetIndices());

	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(3);
	m_VA.AddBuffer(vb, layout);

	Unbind();
}

void Grid::HandleEvents()
{
	m_Input->HandleEvents();
}

void Grid::Update()
{
	m_Input->Update(*this);
}

void Grid::Action(Command command)
{
	switch (command)
	{
	case Command::CHANGE_COLOUR:
		ChangeColour(0, 2, 3, TOP);
		break;
	case Command::CHANGE_COLOUR_2: // Test Colour Change
		ChangeColour(1, 0, 1, TOP);
		break;
	}
}

void Grid::Bind() const
{
	m_VA.Bind();
}

void Grid::Unbind() const
{
	m_VA.Unbind();
}

std::vector<unsigned int> Grid::GetIndices()
{
	std::vector<unsigned int> indices;

	for (unsigned int i = 0; i < m_Vertices.size() / 6; i++)
		indices.insert(indices.end(), { i, ++i, ++i, i, ++i, i - 3 });

	m_Count = indices.size();

	return indices;
}

void Grid::PrepareCubes(const std::vector<std::vector<std::vector<unsigned int>>>& map)
{
	m_Cubes.resize(map.size());
	for (unsigned int k = 0; k < map.size(); k++)
	{
		for (unsigned int j = 0; j < map[k].size(); j++)
		{
			m_Cubes[k].resize(map[k].size());
			bool WestAdded = false;
			for (unsigned int i = 0; i < map[k][j].size(); i++)
			{
				std::vector<Side> sides;
				if (!map[k][j][i]) continue;

				if (k == map.size() - 1 || i > map.at(k + 1).at(j).size() - 1)
					sides.emplace_back(Side{ Face::TOP, Colour::GRAY });

				if (j == 0 || i > map.at(k).at(j - 1).size() - 1 || !map.at(k).at(j - 1).at(i))
					sides.emplace_back(Side{ Face::NORTH, Colour::GRAY });

				if (i == map.at(k).at(j).size() - 1)
					sides.emplace_back(Side{ Face::EAST, Colour::GRAY });

				if (j == map.at(k).size() - 1 || i > map.at(k).at(j + 1).size() - 1 || !map.at(k).at(j + 1).at(i))
					sides.emplace_back(Side{ Face::SOUTH, Colour::GRAY });

				if (!WestAdded)
				{
					sides.emplace_back(Side{ Face::WEST, Colour::GRAY });
					WestAdded = true;
				}
				if (k == 0 || j > map.at(k - 1).size() - 1 || i > map.at(k - 1).at(j).size() - 1)
					sides.emplace_back(Side{ Face::BOTTOM, Colour::GRAY });

				m_Cubes[k][j].emplace_back(Cube(sides, (float)i, (float)k, (float)j));
			}
			CalculatePosition((float)map[k][j].size());
		}
	}
}

void Grid::PrepareVertices(std::vector<std::vector<std::vector<Cube>>>& cubes)
{
	m_Vertices.clear();

	for (unsigned int j = 0; j < cubes.size(); j++)
		for (unsigned int i = 0; i < cubes[j].size(); i++)
			for (Cube& cube : cubes[j][i])
			{
				auto& vertices = cube.GetSides();
				m_Vertices.insert(m_Vertices.end(), vertices.begin(), vertices.end());
			}
}

void Grid::CalculatePosition(float width)
{
	if (m_Position.x > width / 2.0f)
		m_Position.x = width / 2.0f;
}

void Grid::ChangeColour(int x, int y, int z, Face face)
{
	switch (face)
	{
	case TOP: {
		if (!CheckCubeFace(x, y, z, face))
		{
			std::cout << "Top Face doesn't exist at [" << y << "][" << z << "][" << x << "]!" << std::endl;
			break;
		}

		if (!CheckCubeFace(x, y, z - 1, face))
			if (!CheckCubeFace(x, y, z, NORTH))
				CheckCubeFace(x, y + 1, z - 1, SOUTH);

		if (!CheckCubeFace(x + 1, y, z, face))
			if (!CheckCubeFace(x, y, z, EAST))
				CheckCubeFace(x + 1, y + 1, z, WEST);

		if (!CheckCubeFace(x, y, z + 1, face))
			if (!CheckCubeFace(x, y, z, SOUTH))
				CheckCubeFace(x, y + 1, z + 1, NORTH);

		if (!CheckCubeFace(x - 1, y, z, face))
			if (!CheckCubeFace(x, y, z, WEST))
				CheckCubeFace(x - 1, y + 1, z, EAST);
	}
				break;
	case NORTH: {
		if (!CheckCubeFace(x, y, z, face))
		{
			std::cout << "North Face doesn't exist at [" << y << "][" << z << "][" << x << "]!" << std::endl;
			break;
		}

		if (!CheckCubeFace(x, y + 1, z, face))
			if (!CheckCubeFace(x, y, z, TOP))
				CheckCubeFace(x, y + 1, z - 1, BOTTOM);

		if (!CheckCubeFace(x, y - 1, z, face))
			if (!CheckCubeFace(x, y, z, BOTTOM))
				CheckCubeFace(x, y - 1, z - 1, TOP);

		if (!CheckCubeFace(x - 1, y, z, face))
			if (!CheckCubeFace(x, y, z, WEST))
				CheckCubeFace(x - 1, y, z - 1, EAST);

		if (!CheckCubeFace(x + 1, y, z, face))
			if (!CheckCubeFace(x, y, z, EAST))
				CheckCubeFace(x + 1, y, z - 1, EAST);
	}
				break;
	case EAST: { 
		if (!CheckCubeFace(x, y, z, face))
		{
			std::cout << "East Face doesn't exist at [" << y << "][" << z << "][" << x << "]!" << std::endl;
			break;
		}

		if (!CheckCubeFace(x, y + 1, z, face))
			if (!CheckCubeFace(x, y, z, TOP))
				CheckCubeFace(x + 1, y + 1, z, BOTTOM);

		if (!CheckCubeFace(x, y - 1, z, face))
			if (!CheckCubeFace(x, y, z, BOTTOM))
				CheckCubeFace(x + 1, y - 1, z, TOP);

		if (!CheckCubeFace(x, y, z - 1, face))
			if (!CheckCubeFace(x, y, z, NORTH))
				CheckCubeFace(x + 1, y, z - 1, SOUTH);

		if (!CheckCubeFace(x, y, z + 1, face))
			if (!CheckCubeFace(x, y, z, SOUTH))
				CheckCubeFace(x + 1, y, z + 1, NORTH);
	}
				break;
	case SOUTH: {
		if (!CheckCubeFace(x, y, z, face))
		{
			std::cout << "South Face doesn't exist at [" << y << "][" << z << "][" << x << "]!" << std::endl;
			break;
		}

		if (!CheckCubeFace(x, y + 1, z, face))
			if (!CheckCubeFace(x, y, z, TOP))
				CheckCubeFace(x, y + 1, z + 1, BOTTOM);

		if (!CheckCubeFace(x, y - 1, z, face))
			if (!CheckCubeFace(x, y, z, BOTTOM))
				CheckCubeFace(x, y - 1, z + 1, TOP);

		if (!CheckCubeFace(x - 1, y, z, face))
			if (!CheckCubeFace(x, y, z, WEST))
				CheckCubeFace(x - 1, y, z + 1, EAST);

		if (!CheckCubeFace(x + 1, y, z, face))
			if (!CheckCubeFace(x, y, z, EAST))
				CheckCubeFace(x - 1, y, z - 1, WEST);
	}
				break;
	case WEST: {
		if (!CheckCubeFace(x, y, z, face))
		{
			std::cout << "West Face doesn't exist at [" << y << "][" << z << "][" << x << "]!" << std::endl;
			break;
		}

		if (!CheckCubeFace(x, y + 1, z, face))
			if (!CheckCubeFace(x, y, z, TOP))
				CheckCubeFace(x - 1, y + 1, z, BOTTOM);

		if (!CheckCubeFace(x, y - 1, z, face))
			if (!CheckCubeFace(x, y, z, BOTTOM))
				CheckCubeFace(x - 1, y - 1, z, TOP);

		if (!CheckCubeFace(x, y, z - 1, face))
			if (!CheckCubeFace(x, y, z, NORTH))
				CheckCubeFace(x - 1, y, z - 1, SOUTH);

		if (!CheckCubeFace(x, y, z + 1, face))
			if (!CheckCubeFace(x, y, z, SOUTH))
				CheckCubeFace(x - 1, y, z - 1, NORTH);
	}
				break;
	case BOTTOM: {
		if (!CheckCubeFace(x, y, z, face))
		{
			std::cout << "Bottom Face doesn't exist at [" << y << "][" << z << "][" << x << "]!" << std::endl;
			break;
		}

		if (!CheckCubeFace(x, y, z - 1, face))
			if (!CheckCubeFace(x, y, z, NORTH))
				CheckCubeFace(x, y - 1, z - 1, SOUTH);

		if (!CheckCubeFace(x + 1, y, z, face))
			if (!CheckCubeFace(x, y, z, EAST))
				CheckCubeFace(x + 1, y - 1, z, WEST);
		
		if (!CheckCubeFace(x, y, z + 1, face))
			if (!CheckCubeFace(x, y, z, SOUTH))
				CheckCubeFace(x, y - 1, z + 1, NORTH);

		if (!CheckCubeFace(x - 1, y, z, face))
			if (!CheckCubeFace(x, y, z, WEST))
				CheckCubeFace(x - 1, y - 1, z, EAST);
	}
				break;
	default: std::cout << "Face doesn't exist" << std::endl;
	}

	PrepareVertices(m_Cubes);

	Bind();
	glBufferSubData(GL_ARRAY_BUFFER, 0, m_Vertices.size() * sizeof(m_Vertices[0]), m_Vertices.data());
	Unbind();
}

bool Grid::CheckCubeFace(int x, int y, int z, Face face)
{
	if (x < 0 || y < 0 || z < 0)
		return false;

	if (y >= (int)m_Cubes.size() || z >= (int)m_Cubes[y].size() || x >= (int)m_Cubes[y][z].size())
		return false;

	if (m_Cubes[y][z][x].GetFace(face))
		m_Cubes[y][z][x].ChangeColour(face);
	else
		return false;

	return true;
}