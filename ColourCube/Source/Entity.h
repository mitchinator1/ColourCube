#ifndef ENTITY_H
#define ENTITY_H
#include "GLM/glm.hpp"

enum class Command;

class Entity
{
protected:
	glm::vec3 m_Position;
	glm::mat4 m_ModelMatrix;

public:
	Entity() noexcept	: m_Position({ 0.0f, 0.0f, 0.0f }) {};
	virtual ~Entity() {};

	virtual void HandleEvents()				= 0;
	virtual void Update()					= 0;
	virtual void Action(Command command)	= 0;

	virtual glm::vec3& GetPosition()		{ return m_Position; }
	virtual glm::mat4& GetModelMatrix()		{ return m_ModelMatrix; }
};

#endif