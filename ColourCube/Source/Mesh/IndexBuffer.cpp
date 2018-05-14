#include "IndexBuffer.h"
#include "GL/glew.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
	: m_IndicesCount(count)
{
	glGenBuffers(1, &m_RendererID);
	Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

IndexBuffer::IndexBuffer(const std::vector<unsigned int>& data)
	: m_IndicesCount(data.size())
{
	glGenBuffers(1, &m_RendererID);
	UpdateBuffer(data);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void IndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::UpdateBuffer(const std::vector<unsigned int>& indices)
{
	m_IndicesCount = indices.size();
	Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_IndicesCount * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
}

void IndexBuffer::SetCount(unsigned int count)
{
	m_IndicesCount = count;
}