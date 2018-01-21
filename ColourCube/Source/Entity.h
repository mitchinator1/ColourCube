#pragma once
#include "GLM/glm.hpp"

enum class MOVEMENT
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

class Entity
{
private:
	glm::vec3 m_Position;
public:
	virtual void Update() = 0;
	virtual void Move(MOVEMENT dir) = 0;
};