#include "Grid.h"
#include "VertexBufferLayout.h"
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

Grid::Grid()
{
	
}

Grid::Grid(BasicInput* input)
	: m_Input(input)
{
	LoadLevel("Resources/Data/levels.data");
}

Grid::~Grid()
{
	delete m_Input;
}

void Grid::LoadLevel(const std::string& filepath)
{
	std::ifstream stream(filepath);
	std::vector<std::vector<unsigned int>> level;
	std::vector<unsigned int> row;
	unsigned int i;
	while (stream >> i)
	{
		//if (line.find("#level") != std::string::npos)

		row.emplace_back(i);

		if (stream.peek() == '\n')
		{
			level.emplace_back(row);
			row.clear();
		}
	}

	CreateLevel(level);
}

void Grid::CreateLevel(const std::vector<std::vector<unsigned int>> map)
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
		ChangeColour(m_Cubes[1]);
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

void Grid::PrepareCubes(const std::vector<std::vector<unsigned int>>& map)
{
	for (unsigned int j = 0; j < map.size(); j++)
	{
		bool WestAdded = false;
		for (unsigned int i = 0; i < map[j].size(); i++)
		{
			if (!map[j][i])	continue;
			std::vector<Side> sides;

			sides.emplace_back(Side{ Face::TOP, { 0.3f, 0.5f, 0.7f } });

			if (j == 0 || i > map.at(j - 1).size() - 1 || !map.at(j - 1).at(i))
				sides.emplace_back(Side{ Face::NORTH, { 0.3f, 0.5f, 0.7f } });

			if (i == map.at(j).size() - 1)
				sides.emplace_back(Side{ Face::EAST, { 0.3f, 0.5f, 0.7f } });

			if (j == map.size() - 1 || i > map.at(j + 1).size() - 1 || !map.at(j + 1).at(i))
				sides.emplace_back(Side{ Face::SOUTH, { 0.3f, 0.5f, 0.7f } });

			if (!WestAdded)
			{
				sides.emplace_back(Side{ Face::WEST, { 0.3f, 0.5f, 0.7f } });
				WestAdded = true;
			}

			sides.emplace_back(Side{ Face::BOTTOM, { 0.3f, 0.5f, 0.7f } });

			m_Cubes.emplace_back(Cube(sides, (float)i, 0.0f, (float)j));
		}
		CalculatePosition((float)map[j].size());
	}
}

void Grid::PrepareVertices(const std::vector<Cube>& cubes)
{
	m_Vertices.clear();

	for (Cube cube : cubes)
	{
		auto vertices = cube.GetSides();
		m_Vertices.insert(m_Vertices.end(), vertices.begin(), vertices.end());
	}
}

void Grid::CalculatePosition(float width)
{
	if (m_Position.x > width / 2.0f)
		m_Position.x = width / 2.0f;
}

void Grid::ChangeColour(Cube& cube)
{
	Colour colour = Colour::WHITE;
	glm::vec3 newColour;

	switch (colour)
	{
	case Colour::BLACK: newColour = { 0.0f, 0.0f, 0.0f };
		break;
	case Colour::GRAY:	newColour = { 0.5f, 0.5f, 0.5f };
		break;
	case Colour::WHITE: newColour = { 1.0f, 1.0f, 1.0f };
		break;
	default:			newColour = { 1.0f, 0.0f, 0.1f };
	}

	cube.ChangeColour(Face::TOP, newColour );

	PrepareVertices(m_Cubes);

	Bind();
	glBufferSubData(GL_ARRAY_BUFFER, 0, m_Vertices.size() * sizeof(m_Vertices[0]), m_Vertices.data());
	Unbind();
}