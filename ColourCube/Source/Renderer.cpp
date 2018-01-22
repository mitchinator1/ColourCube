#include "Renderer.h"

Renderer::Renderer()
{

}

Renderer::~Renderer()
{

}

void Renderer::Draw(VertexArray& va, IndexBuffer& ib, Shader& shader) const
{
	shader.Bind();
	va.Bind();
	ib.Bind();
	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
	ib.Unbind();
	va.Unbind();
	shader.Unbind();
}

void Renderer::Draw(VertexArray& va, IndexBuffer& ib) const
{
	va.Bind();
	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
	va.Unbind();
}

void Renderer::Draw(Grid& grid) const
{
	grid.Bind();
	glDrawElements(GL_TRIANGLES, grid.GetCount(), GL_UNSIGNED_INT, nullptr);
	grid.Unbind();
}

void Renderer::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT);
}