#pragma once
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include <vector>

class VertexArray
{
private:
	unsigned int m_RendererID;
	unsigned int m_Buffer;

public:
	VertexArray();
	~VertexArray();

	void AddBuffer(VertexBuffer& vb, const VertexBufferLayout& layout);
	void UpdateBuffer(std::vector<float>& vertices);

	void Bind() const;
	void Unbind() const;
private:

};