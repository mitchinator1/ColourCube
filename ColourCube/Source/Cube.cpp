#include "Cube.h"

Cube::Cube(const Sides sides, float x, float y, float z)
	: pos({ x, y, z })
{
	if (sides.Front)	AddFront(true);
	if (sides.Back)		AddBack(true);
	if (sides.Left)		AddLeft(true);
	if (sides.Right)	AddRight(true);
	if (sides.Top)		AddTop(true);
	if (sides.Bottom)	AddBottom(true);
}

void Cube::AddFront(bool lit)
{
	m_Vertices.insert(m_Vertices.end(), {
		pos.x - s,	pos.y - s,	pos.z + s,		col.r, col.g, col.b,
		pos.x + s,	pos.y - s,	pos.z + s,		col.r, col.g, col.b,
		pos.x + s,	pos.y + s,	pos.z + s,	 	col.r, col.g, col.b,
		pos.x - s,	pos.y + s,	pos.z + s,		col.r, col.g, col.b
	});
}
void Cube::AddBack(bool lit)
{
	m_Vertices.insert(m_Vertices.end(), {
		pos.x + s,	pos.y - s,	pos.z - s,		col.r, col.g, col.b,
		pos.x - s,	pos.y - s,	pos.z - s,		col.r, col.g, col.b,
		pos.x - s,	pos.y + s,	pos.z - s,		col.r, col.g, col.b,
		pos.x + s,	pos.y + s,	pos.z - s,		col.r, col.g, col.b
	});
}
void Cube::AddLeft(bool lit)
{
	m_Vertices.insert(m_Vertices.end(), {
		pos.x - s,	pos.y + s,	pos.z + s,		col.r, col.g, col.b,
		pos.x - s,	pos.y + s,	pos.z - s,		col.r, col.g, col.b,
		pos.x - s,	pos.y - s,	pos.z - s,		col.r, col.g, col.b,
		pos.x - s,	pos.y - s,	pos.z + s,		col.r, col.g, col.b
	});
}
void Cube::AddRight(bool lit)
{
	m_Vertices.insert(m_Vertices.end(), {
		pos.x + s,	pos.y - s,	pos.z + s,		col.r, col.g, col.b,
		pos.x + s,	pos.y - s,	pos.z - s,		col.r, col.g, col.b,
		pos.x + s,	pos.y + s,	pos.z - s,		col.r, col.g, col.b,
		pos.x + s,	pos.y + s,	pos.z + s,		col.r, col.g, col.b
	});
}
void Cube::AddTop(bool lit)
{
	m_Vertices.insert(m_Vertices.end(), {
		pos.x - s,	pos.y + s,	pos.z + s,		col.r, col.g, col.b,
		pos.x + s,	pos.y + s,	pos.z + s,		col.r, col.g, col.b,
		pos.x + s,	pos.y + s,	pos.z - s,		col.r, col.g, col.b,
		pos.x - s,	pos.y + s,	pos.z - s,		col.r, col.g, col.b
	});
}
void Cube::AddBottom(bool lit)
{
	m_Vertices.insert(m_Vertices.end(), {
		pos.x - s,	pos.y - s,	pos.z + s,		col.r, col.g, col.b,
		pos.x - s,	pos.y - s,	pos.z - s,		col.r, col.g, col.b,
		pos.x + s,	pos.y - s,	pos.z - s,		col.r, col.g, col.b,
		pos.x + s,	pos.y - s,	pos.z + s,		col.r, col.g, col.b
	});
}
