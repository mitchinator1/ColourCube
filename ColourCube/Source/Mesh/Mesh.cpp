#include "Mesh.h"

Mesh::Mesh(std::vector<float> vertices)
	: m_Vertices(vertices), m_Count(0)
{
	Bind();

	VertexBuffer vb(m_Vertices);
	IndexBuffer ib(CalculateIndices());

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

unsigned int Mesh::GetCount() const
{
	return m_Count;
}

std::vector<unsigned int> Mesh::CalculateIndices()
{
	//TODO: Calculate indices based on m_Vertices
	std::vector<unsigned int> indices;
	return indices;
}