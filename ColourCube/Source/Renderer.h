#pragma once
#include "GL/glew.h"

#include "Grid.h"
#include "Shader.h"

class VertexArray;
class IndexBuffer;

class Renderer
{
public:
	Renderer();
	~Renderer();

	void Clear() const;
	void Draw(VertexArray& va, IndexBuffer& ib, Shader& shader) const;
	void Draw(VertexArray& va, IndexBuffer& ib) const;
	void Draw(Grid& grid) const;
};