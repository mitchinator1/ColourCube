#ifndef LEVEL_SAVER_H
#define LEVEL_SAVER_H
#include <vector>
#include <fstream>

class Cube;
struct Colour;
class Level;

class LevelSaver
{
public:
	LevelSaver(Level* level);

private:
	void AddLevelNumber(std::ofstream& os, const unsigned int levelNumber);
	void AddRows(std::ofstream& os, const std::vector<std::vector<unsigned int>>& rows);
	void AddPossibleColours(std::ofstream& os, const std::vector<Colour> colours);
	void AddCubes(std::ofstream& os, std::vector<Cube>& cubes);

};

#endif