#pragma once
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include <vector>

class VertexArray
{
private:
	unsigned int m_RendererID;
	std::vector<unsigned int> m_Buffers;
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(VertexBuffer& vb, const VertexBufferLayout& layout);

	void BindVB();
	void UnbindVB();
	void Bind() const;
	void Unbind() const;
private:

};