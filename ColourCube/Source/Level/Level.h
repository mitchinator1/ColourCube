#ifndef LEVEL_H
#define LEVEL_H
#include <vector>
#include <memory>
#include "../Entity.h"
#include "Cube.h"
#include "../Mesh/Mesh.h"

namespace Input { 
	class InputBase;
	class MouseBase;
}

class Level : public Entity
{
private:
	glm::vec3 m_Position;
	glm::mat4 m_ModelMatrix;
	std::unique_ptr<Mesh> m_Mesh;
	std::unique_ptr<Input::InputBase> m_KeyInput;
	std::unique_ptr<Input::MouseBase> m_MouseInput;

	std::vector<Cube> m_Cubes;
	std::vector<std::vector<unsigned int>> m_CubeKey;
	std::vector<Colour> m_PossibleColours;
	unsigned int m_CurrentLevel;
	bool m_Updated = false;
	glm::vec3 UpdateCoords = { 0.0f, 0.0f, 0.0f };

public:
	Level(const std::string& levelName, std::unique_ptr<Input::InputBase> input, std::unique_ptr<Input::MouseBase> mouseInput);
	~Level();

	void HandleEvents() override;
	void Update() override;
	void Action(Command command) override;
	glm::vec3& GetPosition() override { return m_Position; }
	glm::mat4& GetModelMatrix() override { return m_ModelMatrix; }

	void Bind() const;
	void Unbind() const;

	bool CheckWin();
	void AddCube(float x, float y, float z, Face face);

	void ChangeColour(int x, int y, int z, Face face);

	inline auto GetCount() { return m_Mesh->GetCount();	}
	inline auto GetCurrentLevel() { return m_CurrentLevel; }
	inline auto& GetCubes() { return m_Cubes; }
	inline auto& GetCubeKey() { return m_CubeKey; }
	inline auto& GetPossibleColours() { return m_PossibleColours; }

private:
	void UpdateVertices();
	void CalculatePosition(glm::vec3& inPosition);
	bool CubeFaceExists(int x, int y, int z, Face face);
};

#endif