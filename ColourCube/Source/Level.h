#pragma once
#include "Mesh/Mesh.h"
#include "Entity.h"
#include "Cube.h"
#include "Input/InputBase.h"
#include "Input/MousePicker.h"

class Level : public Entity
{
private:
	glm::vec3 m_Position;
	glm::mat4 m_ModelMatrix;
	Mesh* m_Mesh;
	std::vector<Cube> m_Cubes;
	std::vector<std::vector<unsigned int>> m_CubeKey;
	std::vector<Colour> m_PossibleColours;
	unsigned int m_CurrentLevel;
	bool m_Updated = false;
	Input::InputBase* m_Input;
	glm::vec3 UpdateCoords = { 0.0f, 0.0f, 0.0f };

public:
	Level();
	Level(Input::InputBase* input);
	~Level();

	void LoadLevel(const std::string& filepath);
	void CreateLevel(const std::vector<int>& level);

	void HandleEvents() override;
	void Update() override;
	void Action(Command command) override;
	const glm::vec3& GetPosition() const override { return m_Position; }
	void Receive(glm::vec3 v) override;
	void Draw() const override;

	void Bind() const;
	void Unbind() const;

	inline const glm::mat4& GetModelMatrix() const { return m_ModelMatrix; }

private:
	void PrepareCubes(const std::vector<int>& data);
	std::vector<float> CalculateVertices();
	void UpdateVertices();
	void CalculatePosition();
	void ChangeColour(int x, int y, int z, Face face);
	bool CheckCubeFace(int x, int y, int z, Face face);
	bool CheckWin();

};