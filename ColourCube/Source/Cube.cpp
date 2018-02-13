#include "Cube.h"
#include <iostream>

Cube::Cube(const std::vector<Side>& sides, float x, float y, float z)
	: m_Position({ x, y, z })
{
	for (const Side& side : sides)
	{
		AddSide(side);
		m_Sides.insert({ side.face, side });
	}
}

const std::vector<float>& Cube::GetSides()
{
	m_Vertices.clear();

	//Update to only update vertices that have changed
	for (const auto &side : m_Sides)
		AddSide(side.second);

	return m_Vertices;
}

void Cube::ChangeColour(Face face)
{
	switch (m_Sides[face].colour)
	{
	case Colour::BLACK:	m_Sides[face].c = { 0.5f, 0.5f, 0.5f };
						m_Sides[face].colour = Colour::GRAY;
						break;
	case Colour::GRAY:	m_Sides[face].c = { 1.0f, 1.0f, 1.0f };
						m_Sides[face].colour = Colour::WHITE;
						break;
	case Colour::WHITE:	m_Sides[face].c = { 0.0f, 0.0f, 0.0f };
						m_Sides[face].colour = Colour::BLACK;
						break;
	}
}

void Cube::AddSide(const Side &side)
{
	glm::vec3 p = m_Position;
	glm::vec3 c;
	switch (side.colour)
	{
	case BLACK: c = { 0.0f, 0.0f, 0.0f };
				break;
	case GRAY:	c = { 0.5f, 0.5f, 0.5f };
			   break;
	case WHITE: c = { 1.0f, 1.0f, 1.0f };
				break;
	default:	c = { 0.7f, 0.4f, 0.3f };
				break;
	}

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

bool Cube::GetFace(Face face)
{
	if (m_Sides.find(face) == m_Sides.end())
		return false;

	return true;
}