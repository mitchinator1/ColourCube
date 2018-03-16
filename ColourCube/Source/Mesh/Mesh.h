#pragma once
#include "VertexArray.h"

class Mesh
{
private:
	VertexArray m_VA;
	std::vector<float> m_Vertices;
	std::vector<unsigned int> m_Indices;
	unsigned int m_Count;

public:
	Mesh(std::vector<float> vertices);
	~Mesh();

	void Bind() const;
	void Unbind() const;

	std::vector<float>& GetVertices();
	void UpdateVertices(std::vector<float> vertices);
	unsigned int GetCount() const;

private:
	void CalculateIndices();
};