#pragma once
#include <vector>
#include "GLM/glm.hpp"

struct Sides
{
	bool Front = false;
	bool FrontLit = false;
	bool Back = false;
	bool BackLit = false;
	bool Left = false;
	bool LeftLit = false;
	bool Right = false;
	bool RightLit = false;
	bool Top = true;
	bool TopLit = false;
	bool Bottom = true;
	bool BottomLit = false;
};

class Cube
{
private:
	const float s = 0.5f;
	glm::vec3 pos;
	glm::vec3 col = { 0.4f, 0.3f, 0.6f };
	std::vector<float> m_Vertices;
public:
	Cube(const Sides sides, float x, float y = 0, float z = 0);

	std::vector<float>& GetSides() { return m_Vertices; }

private:
	void AddFront(bool lit);
	void AddBack(bool lit);
	void AddLeft(bool lit);
	void AddRight(bool lit);
	void AddTop(bool lit);
	void AddBottom(bool lit);

};