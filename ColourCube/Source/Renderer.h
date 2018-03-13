#pragma once
//#include "GL/glew.h"

#include "Entity.h"


class Renderer
{
public:
	Renderer();
	~Renderer();

	void Clear() const;
	//void Draw(VertexArray& va, IndexBuffer& ib, Shader& shader) const;
	//void Draw(VertexArray& va, IndexBuffer& ib) const;
	//void Draw(Level& level) const;
	void Draw(const Entity* entity) const;
};