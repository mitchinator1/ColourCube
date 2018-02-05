#pragma once
#include "Entity.h"
#include "VertexArray.h"
#include "Cube.h"
#include "Input/BasicInput.h"

class Grid : public Entity
{
private:
	glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
	glm::mat4 m_ModelMatrix;
	VertexArray m_VA;
	//std::vector<Cube> m_Cubes;
	std::vector<std::vector<Cube>> m_Cubes;
	std::vector<float> m_Vertices;
	unsigned int m_Count;
	BasicInput* m_Input;

	unsigned int m_X = 5;
	unsigned int m_Z = 0;

public:
	Grid();
	Grid(BasicInput* input);
	~Grid();

	void LoadLevel(const std::string& filepath);
	void CreateLevel(const std::vector<std::vector<unsigned int>>& level);

	void HandleEvents();
	void Update();
	void Action(Command command);
	glm::vec3& GetPosition() { return m_Position; }

	void Bind() const;
	void Unbind() const;

	inline glm::mat4& GetModelMatrix() { return m_ModelMatrix; }
	inline unsigned int& GetCount() { return m_Count; }

private:
	std::vector<unsigned int> GetIndices();
	void PrepareVertices(const std::vector<std::vector<Cube>>& cubes);
	void PrepareCubes(const std::vector<std::vector<unsigned int>>& map);
	void CalculatePosition(float width);
	void ChangeColour(unsigned int x, unsigned int y, unsigned int z, Face face);

};