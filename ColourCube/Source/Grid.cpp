#include "Grid.h"
#include "VertexBufferLayout.h"

Grid::Grid()
{
	float vertices[] = {
		-1.0f, -1.0f,  1.0f,		1.0f, 0.5f, 0.0f,
		 1.0f, -1.0f,  1.0f,		1.0f, 0.5f, 1.0f,
		 1.0f,  1.0f,  1.0f,	 	1.0f, 0.5f, 1.0f,
		-1.0f,  1.0f,  1.0f,		1.0f, 0.5f, 0.0f,
		-1.0f,  1.0f,  1.0f,		1.0f, 0.5f, 0.0f,
		 1.0f,  1.0f,  1.0f,		0.4f, 0.5f, 0.6f,
		 1.0f,  1.0f, -1.0f,		1.0f, 0.5f, 0.0f,
		-1.0f,  1.0f, -1.0f,		1.0f, 0.5f, 0.0f,
		-1.0f,	1.0f, -1.0f,		1.0f, 0.8f, 0.8f,
		-1.0f, -1.0f, -1.0f,		1.0f, 0.4f, 0.7f,
		-1.0f, -1.0f,  1.0f,		0.8f, 0.8f, 0.6f,
		-1.0f,	1.0f,  1.0f,		0.7f, 0.7f, 0.2f,
		 1.0f, -1.0f,  1.0f,		1.0f, 0.8f, 0.8f,
		 1.0f, -1.0f, -1.0f,		1.0f, 0.4f, 0.7f,
		 1.0f,	1.0f, -1.0f,		0.8f, 0.8f, 0.6f,
		 1.0f,	1.0f,  1.0f,		0.7f, 0.7f, 0.2f
	};

	unsigned int indices[] = {
		 0,  1,  2,
		 2,  3,  0,
		 4,  5,  6,
		 6,  7,  4,
		 8,  9, 10,
		10, 11,  8,
		12, 13, 14,
		14, 15, 12
	};

	VertexBuffer vb(vertices, 16 * 6 * sizeof(float));
	IndexBuffer ib(indices, 24);
	m_Count = 24;

	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(3);
	m_VA.AddBuffer(vb, layout);
	Unbind();
}

void Grid::Bind() const
{
	m_VA.Bind();
}

void Grid::Unbind() const
{
	m_VA.Unbind();
}