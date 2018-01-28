#include "Grid.h"
#include "VertexBufferLayout.h"
#include <vector>

Grid::Grid()
{
	glm::vec3 size = { 1.0f, 1.0f, 1.0f };
	glm::vec3 colour = { 0.7f, 0.5f, 0.9f };

	std::vector<float> vertices = {
		-size.x, -size.y,  size.z,		colour.x, colour.y, colour.z,
		 size.x, -size.y,  size.z,		colour.x, colour.y, colour.z,
		 size.x,  size.y,  size.z,	 	colour.x, colour.y, colour.z,
		-size.x,  size.y,  size.z,		colour.x, colour.y, colour.z,
		-size.x,  size.y,  size.z,		colour.x, colour.y, colour.z,
		 size.x,  size.y,  size.z,		colour.x, colour.y, colour.z,
		 size.x,  size.y, -size.z,		colour.x, colour.y, colour.z,
		-size.x,  size.y, -size.z,		colour.x, colour.y, colour.z,
		-size.x,  size.y, -size.z,		colour.x, colour.y, colour.z,
		-size.x, -size.y, -size.z,		colour.x, colour.y, colour.z,
		-size.x, -size.y,  size.z,		colour.x, colour.y, colour.z,
		-size.x,  size.y,  size.z,		colour.x, colour.y, colour.z,
		 size.x, -size.y,  size.z,		colour.x, colour.y, colour.z,
		 size.x, -size.y, -size.z,		colour.x, colour.y, colour.z,
		 size.x,  size.y, -size.z,		colour.x, colour.y, colour.z,
		 size.x,  size.y,  size.z,		colour.x, colour.y, colour.z,
		-size.x, -size.y,  size.z,		colour.x, colour.y, colour.z,
		-size.x, -size.y, -size.z,		colour.x, colour.y, colour.z,
		 size.x, -size.y, -size.z,		colour.x, colour.y, colour.z,
		 size.x, -size.y,  size.z,		colour.x, colour.y, colour.z,
	};

	std::vector<unsigned int> indices;
	for (unsigned int i = 0; i < vertices.size() / 6; i++)
		indices.insert(indices.end(), { i, ++i, ++i, i, ++i, i - 3 });

	VertexBuffer vb(vertices);
	IndexBuffer ib(indices);
	m_Count = indices.size();

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