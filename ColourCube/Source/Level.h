#pragma once
#include "Mesh/Mesh.h"
#include "Entity.h"
#include "Cube.h"
#include "Input/InputBase.h"
#include "Input/MousePicker.h"

#include <memory>

class Level : public Entity
{
private:
	glm::vec3 m_Position;
	glm::mat4 m_ModelMatrix;
	Mesh* m_Mesh;
	std::unique_ptr<Input::InputBase> m_Input;
	std::vector<Cube> m_Cubes;
	std::vector<std::vector<unsigned int>> m_CubeKey;
	std::vector<Colour> m_PossibleColours;
	unsigned int m_CurrentLevel;
	bool m_Updated = false;
	glm::vec3 UpdateCoords = { 0.0f, 0.0f, 0.0f };

public:
	Level();
	Level(std::unique_ptr<Input::InputBase> input);
	~Level();

	void LoadLevel(const std::string& filepath);
	void CreateLevel(const std::vector<int>& level);

	void HandleEvents() override;
	void Update() override;
	void Action(Command command) override;
	glm::vec3& GetPosition() override { return m_Position; }
	void Receive(glm::vec3 v) override;
	void Draw() const override;
	glm::mat4& GetModelMatrix() override { return m_ModelMatrix; }

	void Bind() const;
	void Unbind() const;


private:
	void PrepareCubes(const std::vector<int>& data);
	void UpdateVertices();
	void CalculatePosition();
	void ChangeColour(int x, int y, int z, Face face);
	bool CubeFaceExists(int x, int y, int z, Face face);
	bool CheckWin();

};