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
	Cube(const std::vector<Side>& sides, std::vector<Colour>* colours, float x, float y = 0, float z = 0);
	~Cube() {}
	const std::vector<float>& GetSides();
	void ChangeColour(Face& face);
	bool GetFace(Face& face);

private:
	void AddSide(const Side &side);

};