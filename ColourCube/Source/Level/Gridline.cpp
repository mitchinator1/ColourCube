#include "Gridline.h"

Gridline::Gridline(unsigned int xCount, unsigned int zCount)
	: m_Mesh(nullptr)
{
	auto indices = CreateIndices(xCount, zCount);
	m_Mesh = std::make_unique<Mesh>(CreateVertices(xCount, zCount), 2, 3, indices);
	
}

Gridline::~Gridline()
{

}

void Gridline::Bind() const
{
	m_Mesh->Bind();
}

void Gridline::Unbind() const
{
	m_Mesh->Unbind();
}

std::vector<float> Gridline::CreateVertices(int xCount, int zCount)
{
	std::vector<float> vertices;
	float xMin = -xCount / 2.0f;
	float zMin = -zCount / 2.0f;
	float xMax = xCount / 2.0f;
	float zMax = zCount / 2.0f;

	for (float z = zMin; z < zMax + 1.0f; ++z)
	{
		vertices.insert(vertices.end(), { xMin, -0.5f, z,	1.0f, 1.0f, 1.0f });
		vertices.insert(vertices.end(), { xMax, -0.5f, z,	1.0f, 1.0f, 1.0f });
	}

	for (float x = xMin; x < xMax + 1.0f; ++x)
	{
		vertices.insert(vertices.end(), { x, -0.5f, zMin,	1.0f, 1.0f, 1.0f });
		vertices.insert(vertices.end(), { x, -0.5f, zMax,	1.0f, 1.0f, 1.0f });
	}

	return vertices;
}

std::vector<unsigned int> Gridline::CreateIndices(unsigned int xCount, unsigned int yCount)
{
	std::vector<unsigned int> indices;

	for (unsigned int i = 0; i < xCount * yCount; ++i)
	{
		indices.insert(indices.end(), { i, ++i });
	}

	return indices;
}