#pragma once
#include "GLM/glm.hpp"

enum class Command;

class Entity
{
private:
	glm::vec3 m_Position = { 1.0f, 2.0f, 1.0f };
public:
	Entity() {};
	virtual ~Entity() {};
	virtual void HandleEvents() = 0;
	virtual void Update() = 0;
	virtual void Action(Command command) = 0;
	virtual glm::vec3& GetPosition() { return m_Position; }
	virtual void Receive(glm::vec3 v) = 0;
	virtual void Draw() const = 0;
	virtual glm::mat4& GetModelMatrix() = 0;
};