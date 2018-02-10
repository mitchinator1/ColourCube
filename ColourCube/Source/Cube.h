#pragma once
#include <vector>
#include "GLM/glm.hpp"
#include <unordered_map>

enum Face { TOP, NORTH, EAST, SOUTH, WEST, BOTTOM };

enum Colour { BLACK, GRAY, WHITE };

struct Side
{
	Face face;
	Colour colour;
	glm::vec3 c = { 0.9f, 0.1f, 0.6f }; // Standout colour for default
};

class Cube
{
private:
	const float s = 0.5f;
	glm::vec3 m_Position;
	std::vector<float> m_Vertices;
	std::unordered_map<Face, Side> m_Sides;

public:
	Cube(const std::vector<Side>& Side, float x, float y = 0, float z = 0);
	~Cube() {}
	const std::vector<float>& GetSides() const;
	void ChangeColour(Face face);
	bool GetFace(Face face);

private:
	void AddSide(const Side &side);

};