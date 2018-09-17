#ifndef LEVEL_CREATOR_H
#define LEVEL_CREATOR_H
#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include "GLM/glm.hpp"

class Cube;

class LevelCreator
{
private:
	std::fstream m_Stream;

	std::string m_LevelName;
	unsigned short m_LevelNumber;
	std::vector<glm::vec3> m_PossibleColours;
	std::vector<std::unique_ptr<Cube>> m_Cubes;
	glm::vec3 m_Position;

public:
	LevelCreator(const unsigned int fileNumber = 0);
	~LevelCreator();

	std::vector<float> GetVertices();

	inline auto GetLevelName()			{ return m_LevelName; }
	inline auto GetLevelNumber()		{ return m_LevelNumber; }
	inline auto& GetCubes()				{ return m_Cubes; }
	inline auto& GetPossibleColours()	{ return m_PossibleColours; }
	inline auto& GetPosition()			{ return m_Position; }

private:
	void LoadFile(const std::string& filepath);
	std::vector<short> GetRawCubeData();
	void GetRawColourData();
	void CreateCubes(const std::vector<short>& data);
};

#endif