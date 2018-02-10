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
	std::vector<std::vector<unsigned int>> level;
	std::vector<unsigned int> row;
	unsigned int i;
	std::string line;
	while (stream >> line)
	{
		if (line.find("#level") != std::string::npos)
		{
			stream >> m_CurrentLevel;
			while (stream >> i)
			{
				row.emplace_back(i);

				if (stream.peek() == '\n')
				{
					level.emplace_back(row);
					row.clear();
				}
			}
		}
	}

	CreateLevel(level);
}

void Grid::CreateLevel(const std::vector<std::vector<unsigned int>>& map)
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
		ChangeColour(1, 0, 2, SOUTH);
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

void Grid::PrepareCubes(const std::vector<std::vector<unsigned int>>& map)
{
	m_Cubes.resize(map.size());
	for (unsigned int j = 0; j < map.size(); j++)
	{
		bool WestAdded = false;
		for (unsigned int i = 0; i < map[j].size(); i++)
		{
			std::vector<Side> sides;
			if (!map[j][i]) continue;

			sides.emplace_back(Side{ Face::TOP, Colour::GRAY });

			if (j == 0 || i > map.at(j - 1).size() - 1 || !map.at(j - 1).at(i))
				sides.emplace_back(Side{ Face::NORTH, Colour::GRAY });

			if (i == map.at(j).size() - 1)
				sides.emplace_back(Side{ Face::EAST, Colour::GRAY });

			if (j == map.size() - 1 || i > map.at(j + 1).size() - 1 || !map.at(j + 1).at(i))
				sides.emplace_back(Side{ Face::SOUTH, Colour::GRAY });

			if (!WestAdded)
			{
				sides.emplace_back(Side{ Face::WEST, Colour::GRAY });
				WestAdded = true;
			}

			sides.emplace_back(Side{ Face::BOTTOM, Colour::GRAY });


			m_Cubes[j].emplace_back(Cube(sides, (float)i, 0.0f, (float)j));
		}
		CalculatePosition((float)map[j].size());
	}
}

void Grid::PrepareVertices(const std::vector<std::vector<Cube>>& cubes)
{
	m_Vertices.clear();

	for (unsigned int i = 0; i < cubes.size(); i++)
		for (const Cube& cube : cubes[i])
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

void Grid::ChangeColour(unsigned int x, unsigned int y, unsigned int z, Face face)
{
	/* TO DO:	Tidy up
				Make More Dynamic
				Make 3D
				Take Blank spaces into account
				if top[x + 1] exists, change it. it wouldn't exist with a block on top of it
	*/
	switch (face)
	{
	case TOP: { m_Cubes[z][x].ChangeColour(TOP); //center

		if ((int)x - 1 < 0)
			m_Cubes[z][x].ChangeColour(WEST);
		else
			m_Cubes[z][x - 1].ChangeColour(TOP);

		if ((int)z - 1 >= 0)
			m_Cubes[z - 1][x].ChangeColour(TOP);
		else if ((int)z - 1 < 0)
			m_Cubes[z][x].ChangeColour(NORTH);

		if (x + 1 < m_Cubes[z].size())
			m_Cubes[z][x + 1].ChangeColour(TOP);
		else
			m_Cubes[z][x].ChangeColour(EAST);

		if (z + 1 < m_Cubes.size() && x < m_Cubes[z + 1].size())
			m_Cubes[z + 1][x].ChangeColour(TOP);
		else
			m_Cubes[z][x].ChangeColour(SOUTH);
	}
		break;
	case NORTH: { m_Cubes[z][x].ChangeColour(NORTH);

		m_Cubes[z][x].ChangeColour(BOTTOM);
		m_Cubes[z][x].ChangeColour(TOP);

		if ((int)x - 1 < 0)
			m_Cubes[z][x].ChangeColour(WEST);
		else if ((int)z - 1 > 0 && x == m_Cubes[z - 1].size())
			m_Cubes[z - 1][x - 1].ChangeColour(EAST);
		else
			m_Cubes[z][x - 1].ChangeColour(NORTH);

		if (x + 1 < m_Cubes[z].size())
			m_Cubes[z][x + 1].ChangeColour(NORTH);
		else
			m_Cubes[z][x].ChangeColour(EAST);
	}
		break;
	case EAST: { m_Cubes[z][x].ChangeColour(EAST);

		m_Cubes[z][x].ChangeColour(TOP);
		m_Cubes[z][x].ChangeColour(BOTTOM);

		if ((int)z - 1 < 0)
			m_Cubes[z][x].ChangeColour(NORTH);
		else if (x == m_Cubes[z - 1].size() - 1)
			m_Cubes[z - 1][x].ChangeColour(EAST);
		else
			m_Cubes[z - 1][x + 1].ChangeColour(SOUTH);

		if (z + 1 < m_Cubes.size() && x < m_Cubes[z + 1].size())
			m_Cubes[z + 1][x].ChangeColour(EAST);
		else
			m_Cubes[z][x].ChangeColour(SOUTH);
	}
		break;
	case SOUTH: { m_Cubes[z][x].ChangeColour(SOUTH);
	
		m_Cubes[z][x].ChangeColour(TOP);
		m_Cubes[z][x].ChangeColour(BOTTOM);

		if ((int)x - 1 < 0)
			m_Cubes[z][x].ChangeColour(WEST);
		else if (z + 1 < m_Cubes.size() && x == m_Cubes[z + 1].size())
			m_Cubes[z + 1][x - 1].ChangeColour(EAST);
		else
			m_Cubes[z][x - 1].ChangeColour(SOUTH);

		if (x + 1 < m_Cubes[z].size())
			m_Cubes[z][x + 1].ChangeColour(SOUTH);
		else
			m_Cubes[z][x].ChangeColour(EAST);
	}
		break;
	case WEST: { m_Cubes[z][x].ChangeColour(WEST);
	
		m_Cubes[z][x].ChangeColour(TOP);
		m_Cubes[z][x].ChangeColour(BOTTOM);

		if ((int)z - 1 < 0)
			m_Cubes[z][x].ChangeColour(NORTH);
		else
			m_Cubes[z - 1][x].ChangeColour(WEST);

		if (z + 1 < m_Cubes.size())
			m_Cubes[z + 1][x].ChangeColour(WEST);
		else
			m_Cubes[z][x].ChangeColour(SOUTH);
	}
		break;
	case BOTTOM: { m_Cubes[z][x].ChangeColour(BOTTOM);

		if ((int)x - 1 < 0)
			m_Cubes[z][x].ChangeColour(WEST);
		else
			m_Cubes[z][x - 1].ChangeColour(BOTTOM);

		if ((int)z - 1 < 0)
			m_Cubes[z][x].ChangeColour(NORTH);
		else
			m_Cubes[z - 1][x].ChangeColour(BOTTOM);

		if (x + 1 < m_Cubes[z].size())
			m_Cubes[z][x + 1].ChangeColour(BOTTOM);
		else
			m_Cubes[z][x].ChangeColour(EAST);

		if ((int)z == m_Cubes.size() - 1)
			m_Cubes[z][x].ChangeColour(SOUTH);
		else
			m_Cubes[z + 1][x].ChangeColour(BOTTOM);

	} 
		break;
	}

	PrepareVertices(m_Cubes);

	Bind();
	glBufferSubData(GL_ARRAY_BUFFER, 0, m_Vertices.size() * sizeof(m_Vertices[0]), m_Vertices.data());
	Unbind();
}