#pragma once
#include <vector>
#include "GLM/glm.hpp"

enum Face { TOP, NORTH, EAST, SOUTH, WEST, BOTTOM };
/*
struct Sides
{
	bool Top	= true;
	glm::vec3 TopColour		= { 0.7f, 0.4f, 0.5f };
	bool North	= false;
	glm::vec3 NorthColour	= { 0.7f, 0.4f, 0.5f };
	bool East	= false;
	glm::vec3 EastColour	= { 0.7f, 0.4f, 0.5f };
	bool South	= false;
	glm::vec3 SouthColour	= { 0.7f, 0.4f, 0.5f };
	bool West	= false;
	glm::vec3 WestColour	= { 0.7f, 0.3f, 0.5f };
	bool Bottom = true;
	glm::vec3 BottomColour	= { 0.7f, 0.4f, 0.5f };
};
*/

struct Side
{
	Face face;
	glm::vec3 colour;
};


enum class Colour
{
	BLACK,
	GRAY,
	WHITE
};

class Cube
{
private:
	const float s = 0.5f;
	glm::vec3 m_Position;
	std::vector<float> m_Vertices;
	std::vector<Side> m_Sides;

public:
	Cube(std::vector<Side>& Side, float x, float y = 0, float z = 0);
	std::vector<float>& GetSides();
	void ChangeColour(Face face, glm::vec3 c);

private:
	void AddSide(Side &side);

};