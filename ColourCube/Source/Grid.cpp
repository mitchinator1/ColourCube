#include "Grid.h"
#include "VertexBufferLayout.h"
#include <vector>
#include <iostream>

Grid::Grid()
{
	glm::vec3 p = { 0.0f, 0.0f, 0.0f }; // Position
	glm::vec3 s = { 0.5f, 0.5f, 0.5f }; // Size
	glm::vec3 c = { 0.7f, 0.5f, 0.9f }; // Colour
	/*
	std::vector<float> vertices = {
		p.x - s.x,	p.y - s.y,  p.z + s.z,		c.x, c.y, c.z, // Front
		p.x + s.x,	p.y - s.y,  p.z + s.z,		c.x, c.y, c.z,
		p.x + s.x,	p.y + s.y,	p.z + s.z,	 	c.x, c.y, c.z,
		p.x - s.x,  p.y + s.y,	p.z + s.z,		c.x, c.y, c.z,
		p.x - s.x,  p.y + s.y,	p.z + s.z,		c.x, c.y, c.z, // Top
		p.x + s.x,	p.y + s.y,	p.z + s.z,		c.x, c.y, c.z,
		p.x + s.x,	p.y + s.y,	p.z - s.z,		c.x, c.y, c.z,
		p.x - s.x,  p.y + s.y,	p.z - s.z,		c.x, c.y, c.z,
		p.x - s.x,  p.y + s.y,	p.z - s.z,		c.x, c.y, c.z, // Left
		p.x - s.x,	p.y - s.y,	p.z - s.z,		c.x, c.y, c.z,
		p.x - s.x,	p.y - s.y,  p.z + s.z,		c.x, c.y, c.z,
		p.x - s.x,  p.y + s.y,	p.z + s.z,		c.x, c.y, c.z,
		p.x + s.x,	p.y - s.y,  p.z + s.z,		c.x, c.y, c.z, // Right
		p.x + s.x,	p.y - s.y,	p.z - s.z,		c.x, c.y, c.z,
		p.x + s.x,	p.y + s.y,	p.z - s.z,		c.x, c.y, c.z,
		p.x + s.x,	p.y + s.y,	p.z + s.z,		c.x, c.y, c.z,
		p.x - s.x,	p.y - s.y,  p.z + s.z,		c.x, c.y, c.z, // Bottom
		p.x - s.x,	p.y - s.y,	p.z - s.z,		c.x, c.y, c.z,
		p.x + s.x,	p.y - s.y,	p.z - s.z,		c.x, c.y, c.z,
		p.x + s.x,	p.y - s.y,  p.z + s.z,		c.x, c.y, c.z,
		p.x + s.x,	p.y - s.y,  p.z - s.z,		c.x, c.y, c.z, // Back
		p.x - s.x,	p.y - s.y,	p.z - s.z,		c.x, c.y, c.z,
		p.x - s.x,	p.y + s.y,	p.z - s.z,		c.x, c.y, c.z,
		p.x++ + s.x,	p.y + s.y,  p.z - s.z,		c.x, c.y, c.z,

		p.x - s.x,	p.y - s.y,  p.z + s.z,		c.x, c.y, c.z, // Front
		p.x + s.x,	p.y - s.y,  p.z + s.z,		c.x, c.y, c.z,
		p.x + s.x,	p.y + s.y,	p.z + s.z,	 	c.x, c.y, c.z,
		p.x - s.x,  p.y + s.y,	p.z + s.z,		c.x, c.y, c.z,
		p.x - s.x,  p.y + s.y,	p.z + s.z,		c.x, c.y, c.z, // Top
		p.x + s.x,	p.y + s.y,	p.z + s.z,		c.x, c.y, c.z,
		p.x + s.x,	p.y + s.y,	p.z - s.z,		c.x, c.y, c.z,
		p.x - s.x,  p.y + s.y,	p.z - s.z,		c.x, c.y, c.z,
		p.x - s.x,  p.y + s.y,	p.z - s.z,		c.x, c.y, c.z, // Left
		p.x - s.x,	p.y - s.y,	p.z - s.z,		c.x, c.y, c.z,
		p.x - s.x,	p.y - s.y,  p.z + s.z,		c.x, c.y, c.z,
		p.x - s.x,  p.y + s.y,	p.z + s.z,		c.x, c.y, c.z,
		p.x + s.x,	p.y - s.y,  p.z + s.z,		c.x, c.y, c.z, // Right
		p.x + s.x,	p.y - s.y,	p.z - s.z,		c.x, c.y, c.z,
		p.x + s.x,	p.y + s.y,	p.z - s.z,		c.x, c.y, c.z,
		p.x + s.x,	p.y + s.y,	p.z + s.z,		c.x, c.y, c.z,
		p.x - s.x,	p.y - s.y,  p.z + s.z,		c.x, c.y, c.z, // Bottom
		p.x - s.x,	p.y - s.y,	p.z - s.z,		c.x, c.y, c.z,
		p.x + s.x,	p.y - s.y,	p.z - s.z,		c.x, c.y, c.z,
		p.x + s.x,	p.y - s.y,  p.z + s.z,		c.x, c.y, c.z,
		p.x + s.x,	p.y - s.y,  p.z - s.z,		c.x, c.y, c.z, // Back
		p.x - s.x,	p.y - s.y,	p.z - s.z,		c.x, c.y, c.z,
		p.x - s.x,	p.y + s.y,	p.z - s.z,		c.x, c.y, c.z,
		p.x + s.x,	p.y + s.y,  p.z - s.z,		c.x, c.y, c.z
	};
	*/

	std::vector<std::vector<int>> map = {
		{ 1, 1, 1, 1},
		{ 0, 1, 1 },
		{ 1, 1, 1 }
	};

	glm::vec3 average = {
		0.0f,
		1.0f		/ 2.0f,
		map.size()	/ 2.0f
	};

	std::vector<float> vertices;
	for (unsigned int j = 0; j < map.size(); j++)
	{
		bool LeftAdded = false;
		for (unsigned int i = 0; i < map[j].size(); i++)
		{
			if (!map[j][i])
				continue;
			if (j == map.size() - 1 || i > map.at(j + 1).size() - 1 || !map.at(j + 1).at(i))
				AddFront(vertices, p + glm::vec3{ i, 0, j }, s, c);
			if (j == 0 || i > map.at(j - 1).size() - 1 || !map.at(j - 1).at(i))
				AddBack(vertices, p + glm::vec3{ i, 0, j }, s, c);
			if (!LeftAdded)
			{
				AddLeft(vertices, p + glm::vec3{ i, 0, j }, s, c);
				LeftAdded = true;
			}
			if (i == map[j].size() - 1)
				AddRight(vertices, p + glm::vec3{ i, 0, j }, s, c);

			if (map[j][i])
			{
				AddTop(vertices, p + glm::vec3{ i, 0, j }, s, c);
				AddBottom(vertices, p + glm::vec3{ i, 0, j }, s, c);
			}
		}
		average.x += (float)map[j].size();
	}

	m_Position = { average.x / (float)map.size() / 2.0f, average.y, average.z };

	std::vector<unsigned int> indices;
	for (unsigned int i = 0; i < vertices.size() / 6; i++)
		indices.insert(indices.end(), { i, ++i, ++i, i, ++i, i - 3 });

	VertexBuffer vb(vertices);
	IndexBuffer ib(indices);
	m_Count = indices.size();

	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(3);
	m_VA.AddBuffer(vb, layout);

	Unbind();
}

void Grid::Bind() const
{
	m_VA.Bind();
}

void Grid::Unbind() const
{
	m_VA.Unbind();
}

void Grid::AddFront(std::vector<float>& cube, glm::vec3 p, glm::vec3 s, glm::vec3 c)
{
	cube.insert(cube.end(), {
		p.x - s.x,	p.y - s.y,  p.z + s.z,		c.x, c.y, c.z,
		p.x + s.x,	p.y - s.y,  p.z + s.z,		c.x, c.y, c.z,
		p.x + s.x,	p.y + s.y,	p.z + s.z,	 	c.x, c.y, c.z,
		p.x - s.x,  p.y + s.y,	p.z + s.z,		c.x, c.y, c.z
	});
}

void Grid::AddBack(std::vector<float>& cube, glm::vec3 p, glm::vec3 s, glm::vec3 c)
{
	cube.insert(cube.end(), {
		p.x + s.x, p.y - s.y,	p.z - s.z,		c.x, c.y, c.z,
		p.x - s.x, p.y - s.y,	p.z - s.z,		c.x, c.y, c.z,
		p.x - s.x, p.y + s.y,	p.z - s.z,		c.x, c.y, c.z,
		p.x + s.x, p.y + s.y,	p.z - s.z,		c.x, c.y, c.z,
	});
}

void Grid::AddLeft(std::vector<float>& cube, glm::vec3 p, glm::vec3 s, glm::vec3 c)
{
	cube.insert(cube.end(), {
		p.x - s.x,  p.y + s.y,	p.z - s.z,		c.x, c.y, c.z,
		p.x - s.x,	p.y - s.y,	p.z - s.z,		c.x, c.y, c.z,
		p.x - s.x,	p.y - s.y,  p.z + s.z,		c.x, c.y, c.z,
		p.x - s.x,  p.y + s.y,	p.z + s.z,		c.x, c.y, c.z
	});
}

void Grid::AddRight(std::vector<float>& cube, glm::vec3 p, glm::vec3 s, glm::vec3 c)
{
	cube.insert(cube.end(), {
		p.x + s.x,	p.y - s.y,  p.z + s.z,		c.x, c.y, c.z,
		p.x + s.x,	p.y - s.y,	p.z - s.z,		c.x, c.y, c.z,
		p.x + s.x,	p.y + s.y,	p.z - s.z,		c.x, c.y, c.z,
		p.x + s.x,	p.y + s.y,	p.z + s.z,		c.x, c.y, c.z
	});
}

void Grid::AddTop(std::vector<float>& cube, glm::vec3 p, glm::vec3 s, glm::vec3 c)
{
	cube.insert(cube.end(), {
		p.x - s.x,	p.y + s.y,	p.z + s.z,		c.x, c.y, c.z,
		p.x + s.x,	p.y + s.y,	p.z + s.z,		c.x, c.y, c.z,
		p.x + s.x,	p.y + s.y,	p.z - s.z,		c.x, c.y, c.z,
		p.x - s.x,	p.y + s.y,	p.z - s.z,		c.x, c.y, c.z
	});
}

void Grid::AddBottom(std::vector<float>& cube, glm::vec3 p, glm::vec3 s, glm::vec3 c)
{
	cube.insert(cube.end(), {
		p.x - s.x,	p.y - s.y,  p.z + s.z,		c.x, c.y, c.z,
		p.x - s.x,	p.y - s.y,	p.z - s.z,		c.x, c.y, c.z,
		p.x + s.x,	p.y - s.y,	p.z - s.z,		c.x, c.y, c.z,
		p.x + s.x,	p.y - s.y,  p.z + s.z,		c.x, c.y, c.z
	});
}