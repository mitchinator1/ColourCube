#pragma once
#include "Entity.h"
#include "Mesh/VertexArray.h"
#include "Cube.h"
#include "Input/InputBase.h"
#include "Input/MousePicker.h"

class Grid : public Entity
{
private:
	glm::vec3 m_Position;
	glm::mat4 m_ModelMatrix;
	VertexArray m_VA;
	std::vector<Cube> m_Cubes;
	std::vector<std::vector<unsigned int>> m_CubeKey;
	std::vector<Colour> m_PossibleColours;
	std::vector<float> m_Vertices;
	unsigned int m_Count;
	unsigned int m_CurrentLevel;
	Input::InputBase* m_Input;
	glm::vec3 UpdateCube = { 0.0f, 0.0f, 0.0f };

public:
	Grid();
	Grid(Input::InputBase* input);
	~Grid();

	void LoadLevel(const std::string& filepath);
	void CreateLevel(const std::vector<int>& level);

	void HandleEvents();
	void Update();
	void Action(Command command);
	glm::vec3& GetPosition() { return m_Position; }
	void Receive(glm::vec3 v);

	void Bind() const;
	void Unbind() const;

	inline const glm::mat4& GetModelMatrix() const { return m_ModelMatrix; }
	inline unsigned int& GetCount() { return m_Count; }

private:
	std::vector<unsigned int> GetIndices();
	void PrepareVertices(std::vector<Cube>& cubes);
	void PrepareCubes(const std::vector<int>& data);
	void CalculatePosition();
	void ChangeColour(int x, int y, int z, Face face);
	bool CheckCubeFace(int x, int y, int z, Face face);

};