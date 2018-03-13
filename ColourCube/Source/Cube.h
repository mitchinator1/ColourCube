#pragma once
#include <vector>
#include "GLM/glm.hpp"
#include <unordered_map>
#include <iostream>

enum Face { TOP, NORTH, EAST, SOUTH, WEST, BOTTOM };

struct Colour
{
	Colour(float r, float g, float b) : r(r), g(g), b(b) { }
	float r, g, b;
};

struct Side
{
	Face face;
	int currentColour = 0;
	bool operator==(const Side& rhs)
	{
		return this->currentColour == rhs.currentColour ? true : false;
	}
	bool operator!=(const Side& rhs)
	{
		std::cout << this->currentColour << " : " << rhs.currentColour << std::endl;
		return !(this == &rhs);
	}
};

class Cube
{
private:
	const float s = 0.5f;
	glm::vec3 m_Position;
	std::vector<float> m_Vertices;
	std::vector<Colour>* m_Colours;
	std::unordered_map<Face, Side> m_Sides;

public:
	Cube(const std::vector<Side>& sides, std::vector<Colour>* colours, float x = 0, float y = 0, float z = 0);
	~Cube() {}
	const std::vector<float>& GetSides();
	void ChangeColour(Face face);
	bool CheckFace(Face face);
	Side& getSide(Face face);
	inline const glm::vec3& GetPosition() { return m_Position; }

	//bool operator==(const Cube& lhs, const Cube& rhs);
	/*{
		for (auto& side : this->m_Sides)
			for (const auto& rhsSide : rhs.m_Sides)
				if (side.second != rhsSide.second)
				{
					std::cout << side.second.currentColour << " : " << rhsSide.second.currentColour << std::endl;
					return false;
				}
		return true;
	}*/
	bool operator!=(Cube& rhs)
	{
		return !(this == &rhs);
	}

private:
	void AddSide(const Side &side);
};

bool operator==(const Cube& lhs, const Cube& rhs)
{
	std::cout << "Checking?" << std::endl;
	return true;
}