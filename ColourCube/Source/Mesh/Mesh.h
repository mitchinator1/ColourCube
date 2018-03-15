#pragma once
#include "VertexArray.h"

class Mesh
{
private:
	VertexArray m_VA;
	std::vector<float> m_Vertices;
	std::vector<float> m_Indices;
	unsigned int m_Count;

public:
	Mesh(std::vector<float> vertices);
	~Mesh();

	void Bind() const;
	void Unbind() const;
	unsigned int GetCount() const;

private:
	std::vector<unsigned int> CalculateIndices();
};