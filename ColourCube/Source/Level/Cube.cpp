#include "Cube.h"
#include <iostream>

Cube::Cube(const std::unordered_map<Face, int>& sides, std::vector<glm::vec3>& colours, float x, float y, float z)
	: m_Position({ x, y, z }), m_Colours(colours), m_HighlightColour(nullptr), m_Alpha(1.0f)
{
	for (const auto& side : sides)
	{
		AddFace(side);
	}
}

Cube::~Cube()
{

}

void Cube::ChangeColour(Face face)
{
	++m_Sides[face];
	
	if (m_Sides[face] >= (int)m_Colours.size())
		m_Sides[face] = 0;
}

bool Cube::CheckFace(Face face)
{
	if (m_Sides.find(face) == m_Sides.end())
		return false;

	return true;
}

void Cube::AddFace(Face face, int colour)
{
	if (m_Sides.find(face) != m_Sides.end())
		return;

	m_Sides.insert({ face, colour });
}

void Cube::AddFace(const std::pair<Face, int>& side)
{
	if (m_Sides.find(side.first) != m_Sides.end())
		return;

	m_Sides.insert(side);
}

void Cube::RemoveFace(Face face)
{
	m_Sides.erase(face);
}

Cube* Cube::SetGhost(bool ghost)
{
	m_Ghost = ghost;
	return this;
}

Cube* Cube::SetAlpha(float alpha)
{
	m_Alpha = alpha;
	return this;
}

Cube* Cube::SetColour(float r, float g, float b)
{
	// TODO Should not clear colours, set a highlight colour, and a normal colour
	m_Colours.clear();
	m_Colours.emplace(m_Colours.begin(), glm::vec3{ r, g, b });
	return this;
}

Cube* Cube::SetHighlightColour(glm::vec3* colour)
{
	m_HighlightColour = colour;
	return this;
}

const std::vector<float>& Cube::GetVertices()
{
	m_Vertices.clear();

	CalculateVertices();

	return m_Vertices;
}

bool Cube::operator==(const Cube& rhs)
{
	for (auto& side : this->m_Sides)
	{
		for (const auto& rhsSide : rhs.m_Sides)
		{
			if (side.second != rhsSide.second)
			{
				return false;
			}
		}
	}
	return true;
}

bool Cube::operator!=(const Cube& rhs)
{
	return !(*this == rhs);
}

void Cube::CalculateVertices()
{
	const auto& p = m_Position;

	for (auto& side : m_Sides)
	{
		if (side.second >= m_Colours.size())
		{
			side.second = 0;
		}
		glm::vec3 c = m_Colours.at(side.second);

		if (m_HighlightColour)
		{
			c = *m_HighlightColour;
		}

		auto& s = m_Size;
		auto& a = m_Alpha;

		switch (side.first)
		{
		case Face::TOP: { m_Vertices.insert(m_Vertices.end(), {
			p.x - s,	p.y + s,	p.z + s,	0.0f, 1.0f, 0.0f,		c.r, c.g, c.b, a,
			p.x + s,	p.y + s,	p.z + s,	0.0f, 1.0f, 0.0f,		c.r, c.g, c.b, a,
			p.x + s,	p.y + s,	p.z - s,	0.0f, 1.0f, 0.0f,		c.r, c.g, c.b, a,
			p.x - s,	p.y + s,	p.z - s,	0.0f, 1.0f, 0.0f,		c.r, c.g, c.b, a
			});
		}
			break;
		case Face::NORTH: { m_Vertices.insert(m_Vertices.end(), {
			p.x + s,	p.y - s,	p.z - s,	0.0f, 0.0f, -1.0f,		c.r, c.g, c.b, a,
			p.x - s,	p.y - s,	p.z - s,	0.0f, 0.0f, -1.0f,		c.r, c.g, c.b, a,
			p.x - s,	p.y + s,	p.z - s,	0.0f, 0.0f, -1.0f,		c.r, c.g, c.b, a,
			p.x + s,	p.y + s,	p.z - s,	0.0f, 0.0f, -1.0f,		c.r, c.g, c.b, a
			});
		}
			break;
		case Face::EAST: { m_Vertices.insert(m_Vertices.end(), {
			p.x + s,	p.y - s,	p.z + s,	1.0f, 0.0f, 0.0f,		c.r, c.g, c.b, a,
			p.x + s,	p.y - s,	p.z - s,	1.0f, 0.0f, 0.0f,		c.r, c.g, c.b, a,
			p.x + s,	p.y + s,	p.z - s,	1.0f, 0.0f, 0.0f,		c.r, c.g, c.b, a,
			p.x + s,	p.y + s,	p.z + s,	1.0f, 0.0f, 0.0f,		c.r, c.g, c.b, a
			});
		}
			break;
		case Face::SOUTH: { m_Vertices.insert(m_Vertices.end(), {
			p.x - s,	p.y - s,	p.z + s,	0.0f, 0.0f, 1.0f,		c.r, c.g, c.b, a,
			p.x + s,	p.y - s,	p.z + s,	0.0f, 0.0f, 1.0f,		c.r, c.g, c.b, a,
			p.x + s,	p.y + s,	p.z + s,	0.0f, 0.0f, 1.0f,	 	c.r, c.g, c.b, a,
			p.x - s,	p.y + s,	p.z + s,	0.0f, 0.0f, 1.0f,		c.r, c.g, c.b, a
			});
		}
			break;
		case Face::WEST: { m_Vertices.insert(m_Vertices.end(), {
			p.x - s,	p.y + s,	p.z + s,	-1.0f, 0.0f, 0.0f,		c.r, c.g, c.b, a,
			p.x - s,	p.y + s,	p.z - s,	-1.0f, 0.0f, 0.0f,		c.r, c.g, c.b, a,
			p.x - s,	p.y - s,	p.z - s,	-1.0f, 0.0f, 0.0f,		c.r, c.g, c.b, a,
			p.x - s,	p.y - s,	p.z + s,	-1.0f, 0.0f, 0.0f,		c.r, c.g, c.b, a
			});
		}
			break;
		case Face::BOTTOM: { m_Vertices.insert(m_Vertices.end(), {
			p.x - s,	p.y - s,	p.z + s,	0.0f, -1.0f, 0.0f,		c.r, c.g, c.b, a,
			p.x - s,	p.y - s,	p.z - s,	0.0f, -1.0f, 0.0f,		c.r, c.g, c.b, a,
			p.x + s,	p.y - s,	p.z - s,	0.0f, -1.0f, 0.0f,		c.r, c.g, c.b, a,
			p.x + s,	p.y - s,	p.z + s,	0.0f, -1.0f, 0.0f,		c.r, c.g, c.b, a
			});
		}
			break;
		}
	}
}
