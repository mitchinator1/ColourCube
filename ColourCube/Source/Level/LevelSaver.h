#ifndef LEVEL_SAVER_H
#define LEVEL_SAVER_H
#include <vector>
#include <memory>
#include <fstream>

class Cube;
struct Colour;
class Level;

class LevelSaver
{
private:
	std::ofstream os;

public:
	LevelSaver(Level* level);

private:
	void AddLevelNumber(const unsigned int levelNumber);
	void AddPossibleColours(const std::vector<Colour>& colours);
	void AddCubes(std::vector<std::unique_ptr<Cube>>& cubes);
	void AddLevelName(const std::string& name);

};

#endif