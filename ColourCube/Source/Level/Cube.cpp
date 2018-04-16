#include "Cube.h"
#include <iostream>

Cube::Cube(const std::vector<Side>& sides, std::vector<Colour>& colours, float x, float y, float z)
	: m_Position({ x, y, z }), m_Colours(colours)
{
	for (const auto& side : sides)
	{
		AddSide(side);
		m_Sides.insert({ side.face, side });
	}
}

Cube::~Cube()
{

}

const std::vector<float>& Cube::GetVertices()
{
	m_Vertices.clear();

	CalculateVertices();

	return m_Vertices;
}

void Cube::ChangeColour(Face face)
{
	++m_Sides[face];

	if (m_Sides[face].currentColour >= (int)m_Colours.size())
		m_Sides[face].currentColour = 0;
}

void Cube::AddSide(const Side& side)
{
	m_Sides.insert({ side.face, side });
}

bool Cube::CheckFace(Face face)
{
	if (m_Sides.find(face) == m_Sides.end())
		return false;

	return true;
}

bool Cube::operator==(const Cube& rhs)
{
	for (auto& side : this->m_Sides)
		for (const auto& rhsSide : rhs.m_Sides)
			if (side.second != rhsSide.second)
			{
				return false;
			}

	return true;
}

bool Cube::operator!=(const Cube& rhs)
{
	return !(*this == rhs);
}

void Cube::CalculateVertices()
{
	const glm::vec3& p = m_Position;

	for (auto& side : m_Sides)
	{
		const Colour& c = m_Colours.at(side.second.currentColour);

		switch (side.first)
		{
		case Face::TOP: { m_Vertices.insert(m_Vertices.end(), {
			p.x - s,	p.y + s,	p.z + s,	0.0f, 1.0f, 0.0f,		c.r, c.g, c.b,
			p.x + s,	p.y + s,	p.z + s,	0.0f, 1.0f, 0.0f,		c.r, c.g, c.b,
			p.x + s,	p.y + s,	p.z - s,	0.0f, 1.0f, 0.0f,		c.r, c.g, c.b,
			p.x - s,	p.y + s,	p.z - s,	0.0f, 1.0f, 0.0f,		c.r, c.g, c.b
			});
		}
						break;
		case Face::NORTH: { m_Vertices.insert(m_Vertices.end(), {
			p.x + s,	p.y - s,	p.z - s,	0.0f, 0.0f, -1.0f,		c.r, c.g, c.b,
			p.x - s,	p.y - s,	p.z - s,	0.0f, 0.0f, -1.0f,		c.r, c.g, c.b,
			p.x - s,	p.y + s,	p.z - s,	0.0f, 0.0f, -1.0f,		c.r, c.g, c.b,
			p.x + s,	p.y + s,	p.z - s,	0.0f, 0.0f, -1.0f,		c.r, c.g, c.b
			});
		}
						  break;
		case Face::EAST: { m_Vertices.insert(m_Vertices.end(), {
			p.x + s,	p.y - s,	p.z + s,	1.0f, 0.0f, 0.0f,		c.r, c.g, c.b,
			p.x + s,	p.y - s,	p.z - s,	1.0f, 0.0f, 0.0f,		c.r, c.g, c.b,
			p.x + s,	p.y + s,	p.z - s,	1.0f, 0.0f, 0.0f,		c.r, c.g, c.b,
			p.x + s,	p.y + s,	p.z + s,	1.0f, 0.0f, 0.0f,		c.r, c.g, c.b
			});
		}
						 break;
		case Face::SOUTH: { m_Vertices.insert(m_Vertices.end(), {
			p.x - s,	p.y - s,	p.z + s,	0.0f, 0.0f, 1.0f,		c.r, c.g, c.b,
			p.x + s,	p.y - s,	p.z + s,	0.0f, 0.0f, 1.0f,		c.r, c.g, c.b,
			p.x + s,	p.y + s,	p.z + s,	0.0f, 0.0f, 1.0f,	 	c.r, c.g, c.b,
			p.x - s,	p.y + s,	p.z + s,	0.0f, 0.0f, 1.0f,		c.r, c.g, c.b
			});
		}
						  break;
		case Face::WEST: { m_Vertices.insert(m_Vertices.end(), {
			p.x - s,	p.y + s,	p.z + s,	-1.0f, 0.0f, 0.0f,		c.r, c.g, c.b,
			p.x - s,	p.y + s,	p.z - s,	-1.0f, 0.0f, 0.0f,		c.r, c.g, c.b,
			p.x - s,	p.y - s,	p.z - s,	-1.0f, 0.0f, 0.0f,		c.r, c.g, c.b,
			p.x - s,	p.y - s,	p.z + s,	-1.0f, 0.0f, 0.0f,		c.r, c.g, c.b
			});
		}
						 break;
		case Face::BOTTOM: { m_Vertices.insert(m_Vertices.end(), {
			p.x - s,	p.y - s,	p.z + s,	0.0f, -1.0f, 0.0f,		c.r, c.g, c.b,
			p.x - s,	p.y - s,	p.z - s,	0.0f, -1.0f, 0.0f,		c.r, c.g, c.b,
			p.x + s,	p.y - s,	p.z - s,	0.0f, -1.0f, 0.0f,		c.r, c.g, c.b,
			p.x + s,	p.y - s,	p.z + s,	0.0f, -1.0f, 0.0f,		c.r, c.g, c.b
			});
		}
						   break;
		}
	}
}