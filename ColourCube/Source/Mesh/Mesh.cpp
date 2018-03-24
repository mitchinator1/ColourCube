#include "Mesh.h"
#include "IndexBuffer.h"

#include <iostream>

Mesh::Mesh(std::vector<float>& vertices, unsigned int types, unsigned int numberOfVectors)
	: m_Vertices(vertices), m_Count(0)
{
	Bind();

	VertexBuffer vb(m_Vertices);
	CalculateIndices(types * numberOfVectors);
	IndexBuffer ib(m_Indices);

	VertexBufferLayout layout;
	for (unsigned int i = 0; i < types; ++i)
		layout.Push<float>(numberOfVectors);

	m_VA.AddBuffer(vb, layout);

	Unbind();
}

Mesh::~Mesh()
{

}

void Mesh::Bind() const
{
	m_VA.Bind();
}

void Mesh::Unbind() const
{
	m_VA.Unbind();
}

std::vector<float>& Mesh::GetVertices()
{
	return m_Vertices;
}

void Mesh::UpdateVertices(std::vector<float>& vertices)
{
	m_Vertices = vertices;

	m_VA.UpdateBuffer(m_Vertices);
}

unsigned int Mesh::GetCount() const
{
	return m_Count;
}

void Mesh::CalculateIndices(unsigned int set)
{
	for (unsigned int i = 0; i < m_Vertices.size() / set; ++i)
		m_Indices.insert(m_Indices.end(), { i, ++i, ++i, i, ++i, i - 3 });

	m_Count = m_Indices.size();
}