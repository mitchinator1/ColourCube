#pragma once
#include <vector>
#include "Entity.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"

class Cube : public Entity
{
public:
	Cube();

	void Update();
	void Move(MOVEMENT dir);

	void Bind() const;
	void Unbind() const;
	unsigned int GetCount() const;

	glm::mat4 GetModelMatrix();

private:
	VertexArray m_Va;
	IndexBuffer m_Ib = std::vector<unsigned int>{ 1u, 2u };
};