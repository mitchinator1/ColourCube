#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H
#include <vector>
#include <memory>
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"

class VertexArray
{
private:
	unsigned int m_RendererID;
	std::unique_ptr<VertexBuffer> m_VB;
	std::unique_ptr<IndexBuffer> m_IB;

public:
	VertexArray() noexcept;
	~VertexArray();

	void AddBuffer(std::unique_ptr<VertexBuffer>& vb, const VertexBufferLayout& layout);
	void AddBuffer(std::unique_ptr<IndexBuffer>& ib);

	void UpdateBuffer(const std::vector<float>& vertices);
	void UpdateIndices(const std::vector<unsigned int>& indices);
	void UpdateCount(unsigned int count);

	void Bind() const;
	void Unbind() const;

	inline auto GetCount() const { return m_IB->GetCount(); }

};

#endif