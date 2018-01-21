#include "Cube.h"
#include <iostream>

Cube::Cube()
{
	float vertices[] = {
		-1.0f, -1.0f,  0.0f,		1.0f, 0.5f, 0.0f,
		1.0f, -1.0f,  0.0f,		1.0f, 0.5f, 1.0f,
		1.0f,  1.0f,  0.0f,	 	1.0f, 0.5f, 1.0f,
		-1.0f,  1.0f,  0.0f,		1.0f, 0.5f, 0.0f,
		-1.0f,  1.0f,  0.0f,		1.0f, 0.5f, 0.0f,
		1.0f,  1.0f,  0.0f,		0.4f, 0.5f, 0.6f,
		1.0f,  1.0f, -1.0f,		1.0f, 0.5f, 0.0f,
		-1.0f,  1.0f, -1.0f,		1.0f, 0.5f, 0.0f,
		-1.0f,	1.0f, -1.0f,		1.0f, 0.8f, 0.8f,
		-1.0f, -1.0f, -1.0f,		1.0f, 0.4f, 0.7f,
		-1.0f, -1.0f,  0.0f,		0.8f, 0.8f, 0.6f,
		-1.0f,	1.0f,  0.0f,		0.7f, 0.7f, 0.2f
	};

	VertexBuffer vb(vertices, 12 * 6 * sizeof(float));
	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(3);
	m_Va.AddBuffer(vb, layout);
}

void Cube::Update()
{

}

void Cube::Move(MOVEMENT dir)
{

}

glm::mat4 Cube::GetModelMatrix()
{
	glm::mat4 model;
	return model;
}

void Cube::Bind() const
{
	m_Va.Bind();
	m_Ib.Bind();
}

void Cube::Unbind() const
{
	m_Ib.Unbind();
	m_Va.Unbind();
}

unsigned int Cube::GetCount() const
{
	return m_Ib.GetCount();
}