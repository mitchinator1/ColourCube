#include "Cube.h"
#include <iostream>

Cube::Cube(const std::vector<Side>& sides, std::vector<Colour>* colours, float x, float y, float z)
	: m_Position({ x, y, z }), m_Colours(colours)
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
	for (const auto& side : m_Sides)
		AddSide(side.second);

	return m_Vertices;
}

void Cube::ChangeColour(Face face)
{
	m_Sides[face].currentColour++;
	if (m_Sides[face].currentColour >= (int)m_Colours->size())
		m_Sides[face].currentColour = 0;
}

void Cube::AddSide(const Side &side)
{
	const glm::vec3& p = m_Position;
	const Colour& c = m_Colours->at(side.currentColour);

	switch (side.face)
	{
	case Face::TOP: m_Vertices.insert(m_Vertices.end(), {
		p.x - s,	p.y + s,	p.z + s,	0.0f, 1.0f, 0.0f,		c.r, c.g, c.b,
		p.x + s,	p.y + s,	p.z + s,	0.0f, 1.0f, 0.0f,		c.r, c.g, c.b,
		p.x + s,	p.y + s,	p.z - s,	0.0f, 1.0f, 0.0f,		c.r, c.g, c.b,
		p.x - s,	p.y + s,	p.z - s,	0.0f, 1.0f, 0.0f,		c.r, c.g, c.b
		});
		break;
	case Face::NORTH: m_Vertices.insert(m_Vertices.end(), {
		p.x + s,	p.y - s,	p.z - s,	0.0f, 0.0f, -1.0f,		c.r, c.g, c.b,
		p.x - s,	p.y - s,	p.z - s,	0.0f, 0.0f, -1.0f,		c.r, c.g, c.b,
		p.x - s,	p.y + s,	p.z - s,	0.0f, 0.0f, -1.0f,		c.r, c.g, c.b,
		p.x + s,	p.y + s,	p.z - s,	0.0f, 0.0f, -1.0f,		c.r, c.g, c.b
		});
		break;
	case Face::EAST: m_Vertices.insert(m_Vertices.end(), {
		p.x + s,	p.y - s,	p.z + s,	1.0f, 0.0f, 0.0f,		c.r, c.g, c.b,
		p.x + s,	p.y - s,	p.z - s,	1.0f, 0.0f, 0.0f,		c.r, c.g, c.b,
		p.x + s,	p.y + s,	p.z - s,	1.0f, 0.0f, 0.0f,		c.r, c.g, c.b,
		p.x + s,	p.y + s,	p.z + s,	1.0f, 0.0f, 0.0f,		c.r, c.g, c.b
		});
		break;
	case Face::SOUTH: m_Vertices.insert(m_Vertices.end(), {
		p.x - s,	p.y - s,	p.z + s,	0.0f, 0.0f, 1.0f,		c.r, c.g, c.b,
		p.x + s,	p.y - s,	p.z + s,	0.0f, 0.0f, 1.0f,		c.r, c.g, c.b,
		p.x + s,	p.y + s,	p.z + s,	0.0f, 0.0f, 1.0f,	 	c.r, c.g, c.b,
		p.x - s,	p.y + s,	p.z + s,	0.0f, 0.0f, 1.0f,		c.r, c.g, c.b
		});
		break;
	case Face::WEST: m_Vertices.insert(m_Vertices.end(), {
		p.x - s,	p.y + s,	p.z + s,	-1.0f, 0.0f, 0.0f,		c.r, c.g, c.b,
		p.x - s,	p.y + s,	p.z - s,	-1.0f, 0.0f, 0.0f,		c.r, c.g, c.b,
		p.x - s,	p.y - s,	p.z - s,	-1.0f, 0.0f, 0.0f,		c.r, c.g, c.b,
		p.x - s,	p.y - s,	p.z + s,	-1.0f, 0.0f, 0.0f,		c.r, c.g, c.b
		});
		break;
	case Face::BOTTOM: m_Vertices.insert(m_Vertices.end(), {
		p.x - s,	p.y - s,	p.z + s,	0.0f, -1.0f, 0.0f,		c.r, c.g, c.b,
		p.x - s,	p.y - s,	p.z - s,	0.0f, -1.0f, 0.0f,		c.r, c.g, c.b,
		p.x + s,	p.y - s,	p.z - s,	0.0f, -1.0f, 0.0f,		c.r, c.g, c.b,
		p.x + s,	p.y - s,	p.z + s,	0.0f, -1.0f, 0.0f,		c.r, c.g, c.b
		});
		break;
	}
}

bool Cube::CheckFace(Face face)
{
	if (m_Sides.find(face) == m_Sides.end())
		return false;

	return true;
}

Side& Cube::getSide(Face face)
{
	if (!CheckFace(face))
		std::cout << "Didn't find face" << std::endl;
	return m_Sides[face];
}
