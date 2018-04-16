#include "Gridline.h"

Gridline::Gridline()
	: m_Mesh(nullptr)
{
	m_Mesh = std::make_unique<Mesh>(CreateVertices(), 2, 3);
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

std::vector<float> Gridline::CreateVertices()
{
	std::vector<float> vertices;

	for (unsigned int z = 0; z < 10; ++z)
	{
		//for (unsigned int x = 0; x < 10; ++x)
		//{
			vertices.insert(vertices.end(), { 0.0f, 0.0f, (float)z, 1.0f, 0.5f, 1.0f });
			vertices.insert(vertices.end(), { 11.0f, 0.0f, (float)z, 1.0f, 1.0f, 1.0f });
			vertices.insert(vertices.end(), { 0.0f, 0.0f, (float)z, 1.0f, 0.5f, 1.0f });
		//}
	}

	return vertices;
}
