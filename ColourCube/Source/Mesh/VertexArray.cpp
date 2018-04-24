#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_RendererID);
	Bind();
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_RendererID);
	glDeleteBuffers(1, &m_VertexBuffer);
}

void VertexArray::AddBuffer(VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset);
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
	m_VertexBuffer = vb.GetID();
}

void VertexArray::UpdateBuffer(const std::vector<float>& vertices)
{
	Bind();
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(vertices[0]), vertices.data());
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	Unbind();
}

void VertexArray::UpdateIndices(std::vector<unsigned int>& indices)
{
	Bind();
	

	Unbind();
}

void VertexArray::Bind() const
{
	glBindVertexArray(m_RendererID);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}
