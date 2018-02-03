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
	std::vector<std::vector<unsigned int>> test;
	unsigned int i;
	std::vector<unsigned int> foo;
	while (stream >> i)
	{
		//if (line.find("#level") != std::string::npos)

		foo.emplace_back(i);

		if (stream.peek() == '\n')
		{
			test.emplace_back(foo);
			foo.clear();
		}
	}

	CreateLevel(test);
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
		//ChangeColour(/*fill*/);
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

	for (unsigned int i = 0; i < m_Cubes.size() * 6; i++)
		indices.insert(indices.end(), { i, ++i, ++i, i, ++i, i - 3 });

	m_Count = indices.size();

	return indices;
}

void Grid::PrepareCubes(const std::vector<std::vector<unsigned int>>& map)
{
	for (unsigned int j = 0; j < map.size(); j++)
	{
		bool LeftAdded = false;
		for (unsigned int i = 0; i < map[j].size(); i++)
		{
			Sides sides;
			if (!map[j][i])	continue;

			if (j == map.size() - 1 || i > map.at(j + 1).size() - 1 || !map.at(j + 1).at(i))
				sides.Front = true;

			if (j == 0 || i > map.at(j - 1).size() - 1 || !map.at(j - 1).at(i))
				sides.Back = true;

			if (!LeftAdded)
			{
				sides.Left = true;
				LeftAdded = true;
			}

			if (i == map.at(j).size() - 1)
				sides.Right = true;

			if (map.at(j).at(i) == 2)
				sides.Top = true;

			m_Cubes.emplace_back(Cube(sides, (float)i, 0.0f, (float)j));
		}
		CalculatePosition((float)map[j].size());
	}
}

void Grid::PrepareVertices(const std::vector<Cube>& cubes)
{
	for (Cube cube : cubes)
		m_Vertices.insert(m_Vertices.end(), cube.GetSides().begin(), cube.GetSides().end());
}

void Grid::CalculatePosition(float width)
{
	if (m_Position.x > width / 2.0f)
		m_Position.x = width / 2.0f;
}

void Grid::ChangeColour(Cube& cube)
{
	int x = 1 * 24;
	x += 3;

	Colour colour = Colour::GRAY;
	float newColour;

	switch (colour)
	{
	case Colour::BLACK: newColour = 0.0f;
		break;
	case Colour::GRAY: newColour = 0.5f;
		break;
	case Colour::WHITE: newColour = 1.0f;
		break;
	}

	for (int end = x + 24 ; x < end; x += 3)
	{
		m_Vertices[x++] = newColour;
		m_Vertices[x++] = newColour;
		m_Vertices[x++] = newColour;
	}

	Bind();
	glBufferSubData(GL_ARRAY_BUFFER, 0, m_Vertices.size() * sizeof(m_Vertices[0]), m_Vertices.data());
	Unbind();
}