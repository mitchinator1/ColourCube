#include "Mesh.h"

Mesh::Mesh(const std::vector<float>& vertices, unsigned int count, unsigned int stride, const std::vector<unsigned int>& indices)
{
	m_VA = std::make_unique<VertexArray>();
	Bind();

	VertexBufferLayout layout;
	for (unsigned int i = 0; i < count; ++i)
		layout.Push<float>(stride);

	m_VA->AddBuffer(std::make_unique<VertexBuffer>(vertices), layout);

	auto newIndices = indices;
	if (newIndices.empty())
		newIndices = CalculateIndices(vertices, count * stride);
	m_VA->AddBuffer(std::make_unique<IndexBuffer>(newIndices));

	Unbind();
}

Mesh::~Mesh()
{
	
}

void Mesh::Bind() const
{
	m_VA->Bind();
}

void Mesh::Unbind() const
{
	m_VA->Unbind();
}

void Mesh::UpdateVertices(const std::vector<float>& vertices)
{
	m_VA->UpdateBuffer(vertices);
}

void Mesh::UpdateIndices(const std::vector<unsigned int>& indices)
{
	m_VA->UpdateIndices(indices);
}

void Mesh::UpdateCount(unsigned int count)
{
	m_VA->UpdateCount(count);
}

std::vector<unsigned int> Mesh::CalculateIndices(const std::vector<float>& vertices, unsigned int set)
{
	std::vector<unsigned int> indices;

	for (unsigned int i = 0; i < vertices.size() / set; ++i)
		indices.insert(indices.end(), { i, ++i, ++i, i, ++i, i - 3 });

	return indices;
}