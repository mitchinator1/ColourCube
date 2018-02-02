#include "Cube.h"

Cube::Cube(const Sides sides, float x, float y, float z)
	: pos({ x, y, z })
{
	if (sides.Front)	AddFront(sides.FrontLit);
	if (sides.Back)		AddBack(sides.BackLit);
	if (sides.Left)		AddLeft(sides.LeftLit);
	if (sides.Right)	AddRight(sides.RightLit);
	if (sides.Top)		AddTop(sides.TopLit);
	if (sides.Bottom)	AddBottom(sides.BottomLit);
}

void Cube::AddFront(bool lit)
{
	glm::vec3 c = lit ? glm::vec3{1.0f, 1.0f, 1.0f} : col;
	m_Vertices.insert(m_Vertices.end(), {
		pos.x - s,	pos.y - s,	pos.z + s,		c.r, c.g, c.b,
		pos.x + s,	pos.y - s,	pos.z + s,		c.r, c.g, c.b,
		pos.x + s,	pos.y + s,	pos.z + s,	 	c.r, c.g, c.b,
		pos.x - s,	pos.y + s,	pos.z + s,		c.r, c.g, c.b
	});
}

void Cube::AddBack(bool lit)
{
	glm::vec3 c = lit ? glm::vec3{ 1.0f, 1.0f, 1.0f } : col;
	m_Vertices.insert(m_Vertices.end(), {
		pos.x + s,	pos.y - s,	pos.z - s,		c.r, c.g, c.b,
		pos.x - s,	pos.y - s,	pos.z - s,		c.r, c.g, c.b,
		pos.x - s,	pos.y + s,	pos.z - s,		c.r, c.g, c.b,
		pos.x + s,	pos.y + s,	pos.z - s,		c.r, c.g, c.b
	});
}

void Cube::AddLeft(bool lit)
{
	glm::vec3 c = lit ? glm::vec3{ 1.0f, 1.0f, 1.0f } : col;
	m_Vertices.insert(m_Vertices.end(), {
		pos.x - s,	pos.y + s,	pos.z + s,		c.r, c.g, c.b,
		pos.x - s,	pos.y + s,	pos.z - s,		c.r, c.g, c.b,
		pos.x - s,	pos.y - s,	pos.z - s,		c.r, c.g, c.b,
		pos.x - s,	pos.y - s,	pos.z + s,		c.r, c.g, c.b
	});
}

void Cube::AddRight(bool lit)
{
	glm::vec3 c = lit ? glm::vec3{ 1.0f, 1.0f, 1.0f } : col;
	m_Vertices.insert(m_Vertices.end(), {
		pos.x + s,	pos.y - s,	pos.z + s,		c.r, c.g, c.b,
		pos.x + s,	pos.y - s,	pos.z - s,		c.r, c.g, c.b,
		pos.x + s,	pos.y + s,	pos.z - s,		c.r, c.g, c.b,
		pos.x + s,	pos.y + s,	pos.z + s,		c.r, c.g, c.b
	});
}

void Cube::AddTop(bool lit)
{
	glm::vec3 c = lit ? glm::vec3{ 1.0f, 1.0f, 1.0f } : col;
	m_Vertices.insert(m_Vertices.end(), {
		pos.x - s,	pos.y + s,	pos.z + s,		c.r, c.g, c.b,
		pos.x + s,	pos.y + s,	pos.z + s,		c.r, c.g, c.b,
		pos.x + s,	pos.y + s,	pos.z - s,		c.r, c.g, c.b,
		pos.x - s,	pos.y + s,	pos.z - s,		c.r, c.g, c.b
	});
}

void Cube::AddBottom(bool lit)
{
	glm::vec3 c = lit ? glm::vec3{ 1.0f, 1.0f, 1.0f } : col;
	m_Vertices.insert(m_Vertices.end(), {
		pos.x - s,	pos.y - s,	pos.z + s,		c.r, c.g, c.b,
		pos.x - s,	pos.y - s,	pos.z - s,		c.r, c.g, c.b,
		pos.x + s,	pos.y - s,	pos.z - s,		c.r, c.g, c.b,
		pos.x + s,	pos.y - s,	pos.z + s,		c.r, c.g, c.b
	});
}
