#include "VertexArray.h"
#include <iostream>

VertexArray::VertexArray() noexcept
{
	glGenVertexArrays(1, &m_RendererID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::AddBuffer(std::unique_ptr<VertexBuffer>& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb->Bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset);
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
	vb->Unbind();
	m_VB = std::move(vb);
}

void VertexArray::AddBuffer(std::unique_ptr<IndexBuffer>& ib)
{
	m_IB = std::move(ib);
}

void VertexArray::UpdateBuffer(const std::vector<float>& vertices)
{
	Bind();
	m_VB->UpdateBuffer(vertices);
	Unbind();
}

void VertexArray::UpdateIndices(const std::vector<unsigned int>& indices)
{
	Bind();
	m_IB->UpdateBuffer(indices);
	Unbind();
}

void VertexArray::UpdateCount(unsigned int count)
{
	m_IB->SetCount(count);
}

void VertexArray::Bind() const
{
	glBindVertexArray(m_RendererID);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}
