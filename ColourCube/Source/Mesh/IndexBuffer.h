#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H
#include <vector>

class IndexBuffer
{
private:
	unsigned int m_RendererID;
	unsigned int m_IndicesCount;

public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	IndexBuffer(const std::vector<unsigned int>& data);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	void UpdateBuffer(const std::vector<unsigned int>& indices);
	void SetCount(unsigned int count);

	inline auto GetCount()	const	{ return m_IndicesCount; }
};

#endif