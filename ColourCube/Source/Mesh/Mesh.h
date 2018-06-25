#ifndef MESH_H
#define MESH_H
#include <memory>
#include "VertexArray.h"

class Mesh
{
private:
	std::unique_ptr<VertexArray> m_VA;

public:
	Mesh(const std::vector<float>& vertices, unsigned int count, unsigned int stride, const std::vector<unsigned int>& indices = { });
	Mesh(const std::vector<float>& vertices, const std::vector<unsigned int> strides, const std::vector<unsigned int>& indices = { });
	~Mesh();

	void Bind() const;
	void Unbind() const;

	void UpdateVertices(const std::vector<float>& vertices);
	void UpdateIndices(const std::vector<unsigned int>& indices);
	void UpdateCount(unsigned int count);

	inline auto GetCount() const { return m_VA->GetCount(); }

private:
	std::vector<unsigned int> CalculateIndices(const std::vector<float>& vertices, unsigned int set);
};

#endif