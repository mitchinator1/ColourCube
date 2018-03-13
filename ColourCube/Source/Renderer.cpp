#include "Renderer.h"
#include "GL/glew.h"

Renderer::Renderer()
{

}

Renderer::~Renderer()
{

}

void Renderer::Draw(const Entity* entity) const
{
	entity->Draw();
}

void Renderer::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}