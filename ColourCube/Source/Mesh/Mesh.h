#ifndef MESH_H
#define MESH_H
#include "VertexArray.h"

class Mesh
{
private:
	VertexArray m_VA;
	std::vector<float> m_Vertices;
	std::vector<unsigned int> m_Indices;
	unsigned int m_VertexCount;

public:
	Mesh(const std::vector<float>& vertices, unsigned int count, unsigned int stride);
	~Mesh();

	void Bind() const;
	void Unbind() const;

	void UpdateVertices(const std::vector<float>& vertices);
	void UpdateIndices(std::vector<unsigned int>& indices);

	inline unsigned int GetCount() const { return m_VertexCount; }

private:
	void CalculateIndices(const std::vector<float>& vertices, unsigned int set);
};

#endif