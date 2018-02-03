#include "Cube.h"

Cube::Cube(const Sides sides, float x, float y, float z)
	: m_Position({ x, y, z })
{
	if (sides.Front)	AddFront(sides.FrontColour);
	if (sides.Back)		AddBack(sides.BackColour);
	if (sides.Left)		AddLeft(sides.LeftColour);
	if (sides.Right)	AddRight(sides.RightColour);
	if (sides.Top)		AddTop(sides.TopColour);
	if (sides.Bottom)	AddBottom(sides.BottomColour);
}

void Cube::AddFront(glm::vec3 c)
{
	//glm::vec3 c = lit ? glm::vec3{1.0f, 1.0f, 1.0f} : col;
	glm::vec3 p = m_Position;
	m_Vertices.insert(m_Vertices.end(), {
		p.x - s,	p.y - s,	p.z + s,		c.r, c.g, c.b,
		p.x + s,	p.y - s,	p.z + s,		c.r, c.g, c.b,
		p.x + s,	p.y + s,	p.z + s,	 	c.r, c.g, c.b,
		p.x - s,	p.y + s,	p.z + s,		c.r, c.g, c.b
	});
}

void Cube::AddBack(glm::vec3 c)
{
	//glm::vec3 c = lit ? glm::vec3{ 1.0f, 1.0f, 1.0f } : col;
	glm::vec3 p = m_Position;
	m_Vertices.insert(m_Vertices.end(), {
		p.x + s,	p.y - s,	p.z - s,		c.r, c.g, c.b,
		p.x - s,	p.y - s,	p.z - s,		c.r, c.g, c.b,
		p.x - s,	p.y + s,	p.z - s,		c.r, c.g, c.b,
		p.x + s,	p.y + s,	p.z - s,		c.r, c.g, c.b
	});
}

void Cube::AddLeft(glm::vec3 c)
{
	//glm::vec3 c = lit ? glm::vec3{ 1.0f, 1.0f, 1.0f } : col;
	glm::vec3 p = m_Position;
	m_Vertices.insert(m_Vertices.end(), {
		p.x - s,	p.y + s,	p.z + s,		c.r, c.g, c.b,
		p.x - s,	p.y + s,	p.z - s,		c.r, c.g, c.b,
		p.x - s,	p.y - s,	p.z - s,		c.r, c.g, c.b,
		p.x - s,	p.y - s,	p.z + s,		c.r, c.g, c.b
	});
}

void Cube::AddRight(glm::vec3 c)
{
	//glm::vec3 c = lit ? glm::vec3{ 1.0f, 1.0f, 1.0f } : col;
	glm::vec3 p = m_Position;
	m_Vertices.insert(m_Vertices.end(), {
		p.x + s,	p.y - s,	p.z + s,		c.r, c.g, c.b,
		p.x + s,	p.y - s,	p.z - s,		c.r, c.g, c.b,
		p.x + s,	p.y + s,	p.z - s,		c.r, c.g, c.b,
		p.x + s,	p.y + s,	p.z + s,		c.r, c.g, c.b
	});
}

void Cube::AddTop(glm::vec3 c)
{
	//glm::vec3 c = lit ? glm::vec3{ 1.0f, 1.0f, 1.0f } : col;
	glm::vec3 p = m_Position;
	m_Vertices.insert(m_Vertices.end(), {
		p.x - s,	p.y + s,	p.z + s,		c.r, c.g, c.b,
		p.x + s,	p.y + s,	p.z + s,		c.r, c.g, c.b,
		p.x + s,	p.y + s,	p.z - s,		c.r, c.g, c.b,
		p.x - s,	p.y + s,	p.z - s,		c.r, c.g, c.b
	});
}

void Cube::AddBottom(glm::vec3 c)
{
	//glm::vec3 c = lit ? glm::vec3{ 1.0f, 1.0f, 1.0f } : col;
	glm::vec3 p = m_Position;
	m_Vertices.insert(m_Vertices.end(), {
		p.x - s,	p.y - s,	p.z + s,		c.r, c.g, c.b,
		p.x - s,	p.y - s,	p.z - s,		c.r, c.g, c.b,
		p.x + s,	p.y - s,	p.z - s,		c.r, c.g, c.b,
		p.x + s,	p.y - s,	p.z + s,		c.r, c.g, c.b
	});
}
