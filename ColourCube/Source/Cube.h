#pragma once
#include <vector>
#include "GLM/glm.hpp"

struct Sides
{
	bool Front	= false;
	glm::vec3 FrontColour	= { 0.7f, 0.4f, 0.5f };
	bool Back	= false;
	glm::vec3 BackColour	= { 0.7f, 0.4f, 0.5f };
	bool Left	= false;
	glm::vec3 LeftColour	= { 0.7f, 0.4f, 0.5f };
	bool Right	= false;
	glm::vec3 RightColour	= { 0.7f, 0.4f, 0.5f };
	bool Top	= true;
	glm::vec3 TopColour		= { 0.7f, 0.4f, 0.5f };
	bool Bottom = true;
	glm::vec3 BottomColour	= { 0.7f, 0.4f, 0.5f };
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
public:
	Cube(const Sides sides, float x, float y = 0, float z = 0);

	std::vector<float>& GetSides() { return m_Vertices; }

private:
	void AddFront(glm::vec3 c);
	void AddBack(glm::vec3 c);
	void AddLeft(glm::vec3 c);
	void AddRight(glm::vec3 c);
	void AddTop(glm::vec3 c);
	void AddBottom(glm::vec3 c);

};