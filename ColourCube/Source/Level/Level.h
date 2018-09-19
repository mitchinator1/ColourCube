#ifndef LEVEL_H
#define LEVEL_H
#include <vector>
#include <memory>
#include "../Entity/EntityBase.h"
#include "Cube.h"

namespace Input { class Mouse3D; }
class Mesh;
enum class MOVE_TYPE
	{
		ADD,
		REMOVE,
		PLACE,
		COLOUR
	};

class Level : public Entity::EntityBase
{

private:
	std::unique_ptr<Mesh> m_Mesh;
	std::unique_ptr<Input::Mouse3D> m_MouseInput;

	std::vector<std::unique_ptr<Cube>> m_Cubes;
	std::vector<glm::vec3> m_PossibleColours;
	std::string m_LevelName;
	unsigned int m_CurrentLevel;
	bool m_UpdateNeeded = false;
	bool m_CubesMatch	= false;

	std::vector<std::pair<MOVE_TYPE, glm::vec3>> m_PastMoves;
	std::vector<std::pair<MOVE_TYPE, glm::vec3>> m_FutureMoves;

	const unsigned int MAX_SAVED_MOVES = 10;

public:
	Level(const unsigned int levelNumber, std::unique_ptr<Input::Mouse3D> mouseInput);
	Level(const unsigned int levelNumber, Level* oldLevel);
	~Level();

	void HandleEvents()				override;
	void Update()					override;

	bool CheckWin();

	void Undo();
	void Redo();
	void AddMove(MOVE_TYPE type, float x, float y, float z);
	void RemoveMove(MOVE_TYPE type, float x, float y, float z);

	Cube* AddCube(float x, float y, float z);
	Cube* GetCube(float x, float y, float z);
	void RemoveCube(float x, float y, float z);
	void FillFaces(float x, float y, float z);
	void RemoveFaces(Cube* cube);

	void ToggleMode(MOVE_TYPE type);
	void ChangeMouseInput(std::unique_ptr<Input::Mouse3D> mouseInput);
	void AddColour(glm::vec3& colour);
	void RemoveColours();
	void ChangeColour(int x, int y, int z, Face face);

	void ForceUpdate();

	Mesh* GetMesh();
	inline auto& GetLevelName()			{ return m_LevelName; }
	inline auto GetCurrentLevel()		{ return m_CurrentLevel; }
	inline auto& GetCubes()				{ return m_Cubes; }
	inline auto& GetPossibleColours()	{ return m_PossibleColours; }
	inline auto CubesMatch()			{ if (m_CubesMatch) { m_CubesMatch = false; return true; }  return false; }

private:
	void Init();
	void UpdateVertices();
	void CalculatePosition(glm::vec3& inPosition);
	bool CubeFaceExists(int x, int y, int z, Face face);

};

#endif