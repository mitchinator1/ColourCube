#include "Grid.h"
#include "VertexBufferLayout.h"
#include <vector>
#include <iostream>

Grid::Grid()
{
	
}

Grid::Grid(BasicInput* input)
	: m_Input(input)
{
	
}

Grid::Grid(const std::vector<std::vector<unsigned int>> map)
	: m_Position({0.0f, 1.0f / 2.0f, map.size() / 2.0f})
{
	LoadLevel(map);
}

void Grid::LoadLevel(const std::vector<std::vector<unsigned int>> map)
{
	auto cubes = GetCubes(map);
	m_PositionVertices = GetVertices(cubes);
	auto indices = GetIndices(m_PositionVertices.size(), 6);

	Bind();

	VertexBuffer vb(m_PositionVertices);
	IndexBuffer ib(indices);
	m_Count = indices.size();

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
		ChangeColour(1, 0);
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

std::vector<unsigned int> Grid::GetIndices(const unsigned int total, const unsigned int vSize)
{
	std::vector<unsigned int> indices;

	for (unsigned int i = 0; i < total / vSize; i++)
		indices.insert(indices.end(), { i, ++i, ++i, i, ++i, i - 3 });

	return indices;
}

std::vector<float> Grid::GetVertices(const std::vector<Cube>& cubes)
{
	std::vector<float> vertices;

	for (Cube cube : cubes)
		vertices.insert(vertices.end(), cube.GetSides().begin(), cube.GetSides().end());

	return vertices;
}

std::vector<Cube> Grid::GetCubes(const std::vector<std::vector<unsigned int>>& map)
{
	std::vector<Cube> cubes;

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
				sides.TopLit = true;

			cubes.emplace_back(Cube(sides, (float)i, 0.0f, (float)j));
		}
		CalculatePosition((float)map[j].size());
	}

	return cubes;
}

void Grid::CalculatePosition(float width)
{
	if (m_Position.x > width / 2.0f)
		m_Position.x = width / 2.0f;
}

void Grid::ChangeColour(unsigned int x, unsigned int z)
{

	x *= 24;
	x += 3;

	for (unsigned int end = x + 24 ; x < end; x += 3)
	{
		m_PositionVertices[x++] = 1.0f;
		m_PositionVertices[x++] = 1.0f;
		m_PositionVertices[x++] = 1.0f;
	}

	Bind();
	m_VA.BindVB();
	glBufferData(GL_ARRAY_BUFFER, m_PositionVertices.size() * sizeof(m_PositionVertices[0]), m_PositionVertices.data(), GL_STATIC_DRAW);
	m_VA.UnbindVB();
	Unbind();
}