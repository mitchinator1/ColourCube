#ifndef LEVEL_CREATOR_H
#define LEVEL_CREATOR_H
#include <string>
#include <vector>
#include "GLM/glm.hpp"

struct Colour;
class Cube;

class LevelCreator
{
private:
	unsigned int m_LevelNumber;
	std::vector<std::vector<unsigned int>> m_CubeKey;
	std::vector<Colour> m_PossibleColours;
	std::vector<Cube> m_Cubes;
	glm::vec3 m_Position;

public:
	LevelCreator(const std::string& filename);
	~LevelCreator();

	std::vector<float> GetVertices();

	inline auto GetLevelNumber()		{ return m_LevelNumber; }
	inline auto& GetCubeKey()			{ return m_CubeKey; }
	inline auto& GetCubes()				{ return m_Cubes; }
	inline auto& GetPossibleColours()	{ return m_PossibleColours; }
	inline auto& GetPosition()			{ return m_Position; }

private:
	void LoadFile(const std::string& filepath);
	void CreateCubes(const std::vector<int>& data);
};

#endif