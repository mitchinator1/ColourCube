#include "Mesh.h"
#include "IndexBuffer.h"
#include <iostream>

Mesh::Mesh(const std::vector<float>& vertices, unsigned int count, unsigned int stride, const std::vector<unsigned int>& indices)
	: m_Vertices(vertices), m_Indices(indices), m_VertexCount(0)
{
	Bind();
	VertexBuffer vb(vertices);

	if (m_Indices.empty())
		CalculateIndices(vertices, count * stride);

	m_VertexCount = m_Indices.size();
	IndexBuffer ib(m_Indices);

	VertexBufferLayout layout;
	for (unsigned int i = 0; i < count; ++i)
		layout.Push<float>(stride);

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

void Mesh::UpdateVertices(const std::vector<float>& vertices)
{
	m_Vertices = vertices;

	m_VA.UpdateBuffer(vertices);
}

void Mesh::UpdateIndices(std::vector<unsigned int>& indices)
{
	m_Indices = indices;

	m_VA.UpdateIndices(indices);
}

void Mesh::UpdateCount(unsigned int count)
{
	m_VertexCount = count;
}

void Mesh::CalculateIndices(const std::vector<float>& vertices, unsigned int set)
{
	for (unsigned int i = 0; i < vertices.size() / set; ++i)
		m_Indices.insert(m_Indices.end(), { i, ++i, ++i, i, ++i, i - 3 });
}