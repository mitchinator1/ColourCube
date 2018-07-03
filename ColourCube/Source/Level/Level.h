#ifndef LEVEL_H
#define LEVEL_H
#include <vector>
#include <memory>
#include "../Entity.h"
#include "Cube.h"

namespace Input { 
	class InputBase;
	class Mouse3D;
}

class Mesh;

class Level : public Entity
{
private:
	std::unique_ptr<Mesh> m_Mesh;
	std::unique_ptr<Input::InputBase> m_KeyInput;
	std::unique_ptr<Input::Mouse3D> m_MouseInput;

	std::vector<std::unique_ptr<Cube>> m_Cubes;
	std::vector<glm::vec3> m_PossibleColours;
	std::string m_LevelName;
	unsigned int m_CurrentLevel;
	bool m_UpdateNeeded = false;

public:
	Level(const std::string& levelName, std::unique_ptr<Input::InputBase> input, std::unique_ptr<Input::Mouse3D> mouseInput);
	Level(const std::string& levelName, Level* oldLevel);
	~Level();

	void Init();

	void HandleEvents()				override;
	void Update()					override;
	void Action(Command command)	override;

	//void Bind()						const;
	//void Unbind()					const;

	bool CheckWin();

	Cube* AddCube(float x, float y, float z);
	Cube* GetCube(float x, float y, float z);
	void RemoveCube(float x, float y, float z);
	void FillFaces(float x, float y, float z);
	void RemoveFaces(Cube* cube);

	bool ToggleMode();
	void AddColour(glm::vec3& colour);
	void ChangeColour(int x, int y, int z, Face face);

	void ForceUpdate();

	Mesh* GetMesh();
	//unsigned int GetCount();
	inline auto& GetLevelName()			{ return m_LevelName; }
	inline auto GetCurrentLevel()		{ return m_CurrentLevel; }
	inline auto& GetCubes()				{ return m_Cubes; }
	inline auto& GetPossibleColours()	{ return m_PossibleColours; }

private:
	void UpdateVertices();
	void CalculatePosition(glm::vec3& inPosition);
	bool CubeFaceExists(int x, int y, int z, Face face);

};

#endif