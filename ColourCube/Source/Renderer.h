#pragma once
#include "GL/glew.h"
#include "Cube.h"

#include "Shader.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	void Clear() const;
	void Draw(Cube& cube) const;
};