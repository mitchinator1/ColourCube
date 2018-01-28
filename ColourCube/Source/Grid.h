#pragma once
#include "Entity.h"
#include "VertexArray.h"

class Grid : public Entity
{
private:
	glm::vec3 m_Position;
	glm::mat4 m_ModelMatrix;
	VertexArray m_VA;
	std::vector<float> m_PositionVertices;
	unsigned int m_Count;

public:
	Grid();

	void HandleEvents() {}
	void Update() {}
	void Move(MOVEMENT dir) {}

	void Bind() const;
	void Unbind() const;

	inline glm::mat4& GetModelMatrix() { return m_ModelMatrix; }
	inline unsigned int& GetCount() { return m_Count; }

};