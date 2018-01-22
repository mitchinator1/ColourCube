#pragma once
#include "GL/glew.h"

#include "Grid.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

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