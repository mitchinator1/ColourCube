#pragma once
#include "GLM/glm.hpp"

enum class Command
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN,
	CHANGE_COLOUR,
	CHANGE_COLOUR_2 // Test Command
};

class Entity
{
private:
	glm::vec3 m_Position;
public:
	Entity() {};
	virtual ~Entity() {};
	virtual void HandleEvents() = 0;
	virtual void Update() = 0;
	virtual void Action(Command command) = 0;
	virtual glm::vec3& GetPosition() = 0;
};