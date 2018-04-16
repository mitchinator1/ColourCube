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
	Gridline();
	~Gridline();

	void Bind() const;
	void Unbind() const;

	inline auto& GetModelMatrix() { return m_ModelMatrix; }
	inline auto GetCount() { return m_Mesh->GetCount(); }

private:
	std::vector<float> CreateVertices();
};

#endif