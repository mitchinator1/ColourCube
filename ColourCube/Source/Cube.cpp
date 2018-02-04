#include "Cube.h"

Cube::Cube(std::vector<Side>& sides, float x, float y, float z)
	: m_Position({ x, y, z })
{
	for (Side &side : sides)
		AddSide(side);

	m_Sides = sides;
}

std::vector<float>& Cube::GetSides()
{
	return m_Vertices;
}

void Cube::ChangeColour(Face face, glm::vec3 c)
{
	m_Vertices.clear();
	m_Sides[face].colour = c;

	for (Side &side : m_Sides)
		AddSide(side);
}

void Cube::AddSide(Side &side)
{
	glm::vec3 p = m_Position;
	glm::vec3 c = side.colour;

	switch (side.face)
	{
	case Face::TOP: m_Vertices.insert(m_Vertices.end(), {
		p.x - s,	p.y + s,	p.z + s,		c.r, c.g, c.b,
		p.x + s,	p.y + s,	p.z + s,		c.r, c.g, c.b,
		p.x + s,	p.y + s,	p.z - s,		c.r, c.g, c.b,
		p.x - s,	p.y + s,	p.z - s,		c.r, c.g, c.b
		});
		break;
	case Face::NORTH: m_Vertices.insert(m_Vertices.end(), {
		p.x + s,	p.y - s,	p.z - s,		c.r, c.g, c.b,
		p.x - s,	p.y - s,	p.z - s,		c.r, c.g, c.b,
		p.x - s,	p.y + s,	p.z - s,		c.r, c.g, c.b,
		p.x + s,	p.y + s,	p.z - s,		c.r, c.g, c.b
		});
		break;
	case Face::EAST: m_Vertices.insert(m_Vertices.end(), {
		p.x + s,	p.y - s,	p.z + s,		c.r, c.g, c.b,
		p.x + s,	p.y - s,	p.z - s,		c.r, c.g, c.b,
		p.x + s,	p.y + s,	p.z - s,		c.r, c.g, c.b,
		p.x + s,	p.y + s,	p.z + s,		c.r, c.g, c.b
		});
		break;
	case Face::SOUTH: m_Vertices.insert(m_Vertices.end(), {
		p.x - s,	p.y - s,	p.z + s,		c.r, c.g, c.b,
		p.x + s,	p.y - s,	p.z + s,		c.r, c.g, c.b,
		p.x + s,	p.y + s,	p.z + s,	 	c.r, c.g, c.b,
		p.x - s,	p.y + s,	p.z + s,		c.r, c.g, c.b
		});
		break;
	case Face::WEST: m_Vertices.insert(m_Vertices.end(), {
		p.x - s,	p.y + s,	p.z + s,		c.r, c.g, c.b,
		p.x - s,	p.y + s,	p.z - s,		c.r, c.g, c.b,
		p.x - s,	p.y - s,	p.z - s,		c.r, c.g, c.b,
		p.x - s,	p.y - s,	p.z + s,		c.r, c.g, c.b
		});
		break;
	case Face::BOTTOM: m_Vertices.insert(m_Vertices.end(), {
		p.x - s,	p.y - s,	p.z + s,		c.r, c.g, c.b,
		p.x - s,	p.y - s,	p.z - s,		c.r, c.g, c.b,
		p.x + s,	p.y - s,	p.z - s,		c.r, c.g, c.b,
		p.x + s,	p.y - s,	p.z + s,		c.r, c.g, c.b
		});
		break;
	}
}
