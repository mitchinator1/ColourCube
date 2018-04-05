#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include <vector>

class VertexArray
{
private:
	unsigned int m_RendererID;
	unsigned int m_VertexBuffer;

public:
	VertexArray();
	~VertexArray();

	void AddBuffer(VertexBuffer& vb, const VertexBufferLayout& layout);
	//TODO: Save VBO, update buffer in that
	void UpdateBuffer(const std::vector<float>& vertices);
	void UpdateIndices(std::vector<unsigned int>& indices);

	void Bind() const;
	void Unbind() const;

};

#endif