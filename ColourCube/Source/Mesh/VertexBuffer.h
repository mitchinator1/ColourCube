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

	void Bind() const;
	void Unbind() const;

	void UpdateBuffer(const std::vector<float>& vertices);
};

#endif