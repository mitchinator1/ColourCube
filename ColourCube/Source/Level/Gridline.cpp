#include "Gridline.h"

Gridline::Gridline()
	: m_Mesh(nullptr)
{
	m_Mesh = std::make_unique<Mesh>(CreateVertices(6.0f, 6.0f), 3, 3);
	
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

std::vector<float> Gridline::CreateVertices(float xSize, float zSize)
{
	std::vector<float> vertices;
	xSize += 0.5f;
	zSize += 0.5f;

	for (float z = -3.5f; z < xSize; ++z)
	{
		for (float x = -3.5f; x < xSize; ++x)
		{
			vertices.insert(vertices.end(), { x, -0.5f, z,					0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f });
			vertices.insert(vertices.end(), { x, -0.5f, z + 1.0f,			0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f });
			vertices.insert(vertices.end(), { x + 1.0f, -0.5f, z + 1.0f,	0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f });
			vertices.insert(vertices.end(), { x + 1.0f, -0.5f, z,			0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f });
		}
	}

	return vertices;
}
