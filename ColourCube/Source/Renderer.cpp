#include "Renderer.h"

Renderer::Renderer()
{

}

Renderer::~Renderer()
{

}

void Renderer::Draw(Cube& cube) const
{
	cube.Bind();
	glDrawElements(GL_TRIANGLES, cube.GetCount(), GL_UNSIGNED_INT, nullptr);
	cube.Unbind();
}

void Renderer::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT);
}