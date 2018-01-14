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
	ib.Bind();
	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
	ib.Unbind();
	va.Unbind();
}