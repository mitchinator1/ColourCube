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
	LoadLevel("Resources/Data/TestLevel.data");
	std::cout << "Level " << m_CurrentLevel << " loaded." << std::endl;
}

Grid::~Grid()
{
	delete m_Input;
}

void Grid::LoadLevel(const std::string& filepath)
{
	std::ifstream stream(filepath);
	int i;
	std::string line;
	std::vector<int> data;

	while (stream >> line)
	{
		if (line.find("#level") != std::string::npos)
			stream >> m_CurrentLevel;

		while (stream >> i)
		{
			if (i == 9)
				break;
			data.emplace_back(i);
			if (stream.peek() == '\n')
			{
				m_CubeKey.emplace_back(data);
				data.clear();
			}
		}

		while (stream >> i)
			data.emplace_back(i);
	}

	CreateLevel(data);
}

void Grid::CreateLevel(const std::vector<int>& data)
{
	PrepareCubes(data);
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
		ChangeColour(1, 0, 1, TOP);
		break;
	case Command::CHANGE_COLOUR_2: // Test Colour Change
		ChangeColour(1, 1, 0, EAST);
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

void Grid::PrepareCubes(const std::vector<int>& data)
{
	for (unsigned int i = 0; i < data.size(); i += 15)
	{
		std::vector<Side> sides;
		if (data[i + 3])
			sides.emplace_back(Side{ Face::TOP, (Colour)data[i + 9] });
		if (data[i + 4])
			sides.emplace_back(Side{ Face::NORTH, (Colour)data[i + 10] });
		if (data[i + 5])
			sides.emplace_back(Side{ Face::EAST, (Colour)data[i + 11] });
		if (data[i + 6])
			sides.emplace_back(Side{ Face::SOUTH, (Colour)data[i + 12] });
		if (data[i + 7])
			sides.emplace_back(Side{ Face::WEST, (Colour)data[i + 13] });
		if (data[i + 8])
			sides.emplace_back(Side{ Face::BOTTOM, (Colour)data[i + 14] });

		m_Cubes.emplace_back(Cube(sides, (float)data[i], (float)data[i + 1], (float)data[i + 2]));
	}
}

void Grid::PrepareVertices(std::vector<Cube>& cubes)
{
	m_Vertices.clear();

	for (Cube& cube : cubes)
	{
		auto& vertices = cube.GetSides();
		m_Vertices.insert(m_Vertices.end(), vertices.begin(), vertices.end());
	}
}

void Grid::CalculatePosition(float width)
{
	//TO DO: get proper position
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
			std::cout << "Top Face doesn't exist at [" << x << "][" << y << "][" << z << "]!" << std::endl;
			break;
		}

		if (!CheckCubeFace(x, y, z, NORTH))
			if (!CheckCubeFace(x, y, z - 1, face))
				CheckCubeFace(x, y + 1, z - 1, SOUTH);

		if (!CheckCubeFace(x, y, z, EAST))
			if (!CheckCubeFace(x + 1, y, z, face))
				CheckCubeFace(x + 1, y + 1, z, WEST);

		if (!CheckCubeFace(x, y, z, SOUTH))
			if (!CheckCubeFace(x, y, z + 1, face))
				CheckCubeFace(x, y + 1, z + 1, NORTH);

		if (!CheckCubeFace(x, y, z, WEST))
			if (!CheckCubeFace(x - 1, y, z, face))
				CheckCubeFace(x - 1, y + 1, z, EAST);
	}
				break;
	case NORTH: {
		if (!CheckCubeFace(x, y, z, face))
		{
			std::cout << "North Face doesn't exist at [" << x << "][" << y << "][" << z << "]!" << std::endl;
			break;
		}

		if (!CheckCubeFace(x, y, z, TOP))
			if (!CheckCubeFace(x, y + 1, z, face))
				CheckCubeFace(x, y + 1, z - 1, BOTTOM);

		if (!CheckCubeFace(x, y, z, BOTTOM))
			if (!CheckCubeFace(x, y - 1, z, face))
				CheckCubeFace(x, y - 1, z - 1, TOP);

		if (!CheckCubeFace(x, y, z, WEST))
			if (!CheckCubeFace(x - 1, y, z, face))
				CheckCubeFace(x - 1, y, z - 1, EAST);

		if (!CheckCubeFace(x, y, z, EAST))
			if (!CheckCubeFace(x + 1, y, z, face))
				CheckCubeFace(x + 1, y, z - 1, EAST);
	}
				break;
	case EAST: { 
		if (!CheckCubeFace(x, y, z, face))
		{
			std::cout << "East Face doesn't exist at [" << x << "][" << y << "][" << z << "]!" << std::endl;
			break;
		}

		if (!CheckCubeFace(x, y, z, TOP))
			if (!CheckCubeFace(x, y + 1, z, face))
				CheckCubeFace(x + 1, y + 1, z, BOTTOM);

		if (!CheckCubeFace(x, y, z, BOTTOM))
			if (!CheckCubeFace(x, y - 1, z, face))
				CheckCubeFace(x + 1, y - 1, z, TOP);

		if (!CheckCubeFace(x, y, z, NORTH))
			if (!CheckCubeFace(x, y, z - 1, face))
				CheckCubeFace(x + 1, y, z - 1, SOUTH);

		if (!CheckCubeFace(x, y, z, SOUTH))
			if (!CheckCubeFace(x, y, z + 1, face))
				CheckCubeFace(x + 1, y, z + 1, NORTH);
	}
				break;
	case SOUTH: {
		if (!CheckCubeFace(x, y, z, face))
		{
			std::cout << "South Face doesn't exist at [" << x << "][" << y << "][" << z << "]!" << std::endl;
			break;
		}

		if (!CheckCubeFace(x, y, z, TOP))
			if (!CheckCubeFace(x, y + 1, z, face))
				CheckCubeFace(x, y + 1, z + 1, BOTTOM);

		if (!CheckCubeFace(x, y, z, BOTTOM))
			if (!CheckCubeFace(x, y - 1, z, face))
				CheckCubeFace(x, y - 1, z + 1, TOP);

		if (!CheckCubeFace(x, y, z, WEST))
			if (!CheckCubeFace(x - 1, y, z, face))
				CheckCubeFace(x - 1, y, z + 1, EAST);

		if (!CheckCubeFace(x, y, z, EAST))
			if (!CheckCubeFace(x + 1, y, z, face))
				CheckCubeFace(x - 1, y, z - 1, WEST);
	}
				break;
	case WEST: {
		if (!CheckCubeFace(x, y, z, face))
		{
			std::cout << "West Face doesn't exist at [" << x << "][" << y << "][" << z << "]!" << std::endl;
			break;
		}

		if (!CheckCubeFace(x, y, z, TOP))
			if (!CheckCubeFace(x, y + 1, z, face))
				CheckCubeFace(x - 1, y + 1, z, BOTTOM);

		if (!CheckCubeFace(x, y, z, BOTTOM))
			if (!CheckCubeFace(x, y - 1, z, face))
				CheckCubeFace(x - 1, y - 1, z, TOP);

		if (!CheckCubeFace(x, y, z, NORTH))
			if (!CheckCubeFace(x, y, z - 1, face))
				CheckCubeFace(x - 1, y, z - 1, SOUTH);

		if (!CheckCubeFace(x, y, z, SOUTH))
			if (!CheckCubeFace(x, y, z + 1, face))
				CheckCubeFace(x - 1, y, z - 1, NORTH);
	}
				break;
	case BOTTOM: {
		if (!CheckCubeFace(x, y, z, face))
		{
			std::cout << "Bottom Face doesn't exist at [" << x << "][" << y << "][" << z << "]!" << std::endl;
			break;
		}

		if (!CheckCubeFace(x, y, z, NORTH))
			if (!CheckCubeFace(x, y, z - 1, face))
				CheckCubeFace(x, y - 1, z - 1, SOUTH);

		if (!CheckCubeFace(x, y, z, EAST))
			if (!CheckCubeFace(x + 1, y, z, face))
				CheckCubeFace(x + 1, y - 1, z, WEST);
		
		if (!CheckCubeFace(x, y, z, SOUTH))
			if (!CheckCubeFace(x, y, z + 1, face))
				CheckCubeFace(x, y - 1, z + 1, NORTH);

		if (!CheckCubeFace(x, y, z, WEST))
			if (!CheckCubeFace(x - 1, y, z, face))
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

	if (y >= m_CubeKey.size() || z >= m_CubeKey[y].size() || x > m_CubeKey[y][z])
		return false;
	
	int index = 0;
	for (int i = 0; i < y; i++)
		for (int j = 0; j < m_CubeKey[i].size(); j++)
			index += m_CubeKey[i][j];

	index += z * m_CubeKey[y].size();

	index += x;

	if (m_Cubes[index].GetFace(face))
		m_Cubes[index].ChangeColour(face);
	else
		return false;

	return true;
}
