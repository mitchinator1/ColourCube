#include "Mesh.h"

Mesh::Mesh(std::vector<float> vertices)
	: m_Vertices(vertices), m_Count(0)
{
	Bind();

	VertexBuffer vb(m_Vertices);
	CalculateIndices();
	IndexBuffer ib(m_Indices);

	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(3);
	layout.Push<float>(3);
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

void Mesh::UpdateVertices(std::vector<float> vertices)
{
	//Update vertices here
	m_Vertices = vertices;

	Bind();
	glBufferSubData(GL_ARRAY_BUFFER, 0, m_Vertices.size() * sizeof(m_Vertices[0]), m_Vertices.data());
	Unbind();
}

unsigned int Mesh::GetCount() const
{
	return m_Count;
}

void Mesh::CalculateIndices()
{
	for (unsigned int i = 0; i < m_Vertices.size() / 6; ++i)
		m_Indices.insert(m_Indices.end(), { i, ++i, ++i, i, ++i, i - 3 });

	m_Count = m_Indices.size();
}