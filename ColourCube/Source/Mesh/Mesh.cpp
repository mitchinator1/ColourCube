#include "Mesh.h"
#include "Texture.h"

Mesh::Mesh(const std::vector<float>& vertices, unsigned int count, unsigned int stride, const std::vector<unsigned int>& indices)
	: m_Mode(GL_TRIANGLES), m_Texture(nullptr)
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

Mesh::Mesh(const std::vector<float>& vertices, const std::vector<unsigned int> strides, const std::vector<unsigned int>& indices)
	: m_Mode(GL_TRIANGLES), m_Texture(nullptr)
{
	m_VA = std::make_unique<VertexArray>();
	Bind();

	VertexBufferLayout layout;
	unsigned int indicesCount = 0;
	for (unsigned int i = 0; i < strides.size(); ++i)
	{
		layout.Push<float>(strides[i]);
		indicesCount += strides[i];
	}

	m_VA->AddBuffer(std::make_unique<VertexBuffer>(vertices), layout);

	auto newIndices = indices;
	if (newIndices.empty())
		newIndices = CalculateIndices(vertices, indicesCount);
	m_VA->AddBuffer(std::make_unique<IndexBuffer>(newIndices));

	Unbind();
}

Mesh::~Mesh()
{
	
}

void Mesh::Bind() const
{
	m_VA->Bind();
	if (m_Texture)
	{
		m_Texture->Bind();
	}
}

void Mesh::Unbind() const
{
	m_VA->Unbind();
	if (m_Texture)
	{
		m_Texture->Unbind();
	}
}

void Mesh::UpdateVertices(const std::vector<float>& vertices, unsigned int set)
{
	m_VA->UpdateBuffer(vertices);
	m_VA->UpdateIndices(CalculateIndices(vertices, set));
}

void Mesh::UpdateIndices(const std::vector<unsigned int>& indices)
{
	m_VA->UpdateIndices(indices);
}

void Mesh::UpdateCount(unsigned int count)
{
	m_VA->UpdateCount(count);
}

void Mesh::SetTexture(std::shared_ptr<Texture>& texture)
{
	m_Texture = texture;
}

void Mesh::SetMode(unsigned int mode)
{
	m_Mode = mode;
}

std::vector<unsigned int> Mesh::CalculateIndices(const std::vector<float>& vertices, unsigned int set)
{
	std::vector<unsigned int> indices;

	for (unsigned int i = 0; i < vertices.size() / set; ++i)
		indices.insert(indices.end(), { i, ++i, ++i, i, ++i, i - 3 });

	return indices;
}