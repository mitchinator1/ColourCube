#ifndef GRIDLINE_H
#define GRIDLINE_H
#include <memory>
#include <vector>
#include "../Mesh/Mesh.h"
#include "GLM/glm.hpp"

class Gridline
{
private:
	std::unique_ptr<Mesh> m_Mesh;
	glm::mat4 m_ModelMatrix;

public:
	Gridline(unsigned int xCount, unsigned int zCount);
	~Gridline();

	void Bind() const;
	void Unbind() const;

	inline auto& GetModelMatrix() { return m_ModelMatrix; }
	inline auto GetCount() { return m_Mesh->GetCount(); }

private:
	std::vector<float> CreateVertices(int xCount, int zCount);
	std::vector<unsigned int> CreateIndices(unsigned int xCount, unsigned int yCount);
};

#endif