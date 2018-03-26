#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H
#include <vector>

class VertexBuffer
{
private:
	unsigned int m_RendererID;

public:
	VertexBuffer(const void* data, unsigned int size);
	VertexBuffer(const std::vector<float>& data);
	~VertexBuffer();

	unsigned int GetID() const { return m_RendererID; }
	void Bind() const;
	void Unbind() const;
};

#endif