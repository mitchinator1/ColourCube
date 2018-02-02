#pragma once
#include "Entity.h"
#include "VertexArray.h"
#include "Cube.h"
#include <vector>
#include "Input/BasicInput.h"

class Grid : public Entity
{
private:
	glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
	glm::mat4 m_ModelMatrix;
	VertexArray m_VA;
	std::vector<float> m_PositionVertices;
	unsigned int m_Count;
	BasicInput* m_Input;

public:
	Grid();
	Grid(BasicInput* input);
	Grid(const std::vector<std::vector<unsigned int>> map);

	void LoadLevel(const std::vector<std::vector<unsigned int>> level);

	void HandleEvents();
	void Update();
	void Action(Command command);
	glm::vec3& GetPosition() { return m_Position; }

	void Bind() const;
	void Unbind() const;

	inline glm::mat4& GetModelMatrix() { return m_ModelMatrix; }
	inline unsigned int& GetCount() { return m_Count; }

private:
	std::vector<unsigned int> GetIndices(const unsigned int total, const unsigned int vSize);
	std::vector<float> GetVertices(const std::vector<Cube>& cubes);
	std::vector<Cube> GetCubes(const std::vector<std::vector<unsigned int>>& map);
	void CalculatePosition(float width);
	void ChangeColour(unsigned int x, unsigned int z);

};