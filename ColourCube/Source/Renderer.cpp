#include "Renderer.h"

Renderer::Renderer()
{

}

Renderer::~Renderer()
{

}

void Renderer::Draw(VertexArray& va, IndexBuffer& ib, Shader& shader)
{
	shader.Bind();
	va.Bind();
	ib.Bind();
	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
	ib.Unbind();
	va.Unbind();
	shader.Unbind();
}