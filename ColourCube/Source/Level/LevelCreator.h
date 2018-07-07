#ifndef LEVEL_CREATOR_H
#define LEVEL_CREATOR_H
#include <string>
#include <vector>
#include <memory>
#include "GLM/glm.hpp"

class Cube;

class LevelCreator
{
private:
	unsigned short m_LevelNumber;
	std::vector<glm::vec3> m_PossibleColours;
	std::vector<std::unique_ptr<Cube>> m_Cubes;
	glm::vec3 m_Position;

public:
	LevelCreator(const std::string& filename);
	~LevelCreator();

	std::vector<float> GetVertices();

	inline auto GetLevelNumber()		{ return m_LevelNumber; }
	inline auto& GetCubes()				{ return m_Cubes; }
	inline auto& GetPossibleColours()	{ return m_PossibleColours; }
	inline auto& GetPosition()			{ return m_Position; }

private:
	void LoadFile(const std::string& filepath);
	void CreateCubes(const std::vector<short>& data);
};

#endif