#ifndef CUBE_H
#define CUBE_H
#include <vector>
#include <unordered_map>
#include "GLM/glm.hpp"

enum class Face {
	TOP		= 0,
	NORTH	= 1,
	EAST	= 2,
	SOUTH	= 3,
	WEST	= 4,
	BOTTOM	= 5 };

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
		return (this->currentColour == rhs.currentColour) ? true : false;
	}
	bool operator!=(const Side& rhs)
	{
		return !(this->operator==(rhs));
	}
	Side& operator++()
	{
		++this->currentColour;
		return *this;
	}
};

class Cube
{
private:
	float s = 0.5f;
	glm::vec3 m_Position;
	std::vector<float> m_Vertices;
	std::vector<Colour> m_Colours;
	std::unordered_map<Face, Side> m_Sides;

public:
	Cube(const std::vector<Side>& sides, std::vector<Colour>& colours, float x = 0, float y = 0, float z = 0);
	~Cube();

	const std::vector<float>& GetSides();
	void ChangeColour(Face face);
	bool CheckFace(Face face);
	inline const glm::vec3& GetPosition() { return m_Position; }

	bool operator==(const Cube& rhs);
	bool operator!=(const Cube& rhs);

private:
	void AddSide(const Side &side);
};

#endif