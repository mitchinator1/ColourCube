#include "LevelSaver.h"
#include <string>
#include "Level.h"
#include "Cube.h"

LevelSaver::LevelSaver(Level* level)
{
	const std::string file = "Resources/Data/" + level->GetLevelName() + ".data";
	os.open(file);

	AddLevelNumber(level->GetCurrentLevel());
	AddPossibleColours(level->GetPossibleColours());
	AddCubes(level->GetCubes());

	os.close();

	AddLevelName(level->GetLevelName());
}

void LevelSaver::AddLevelNumber(const unsigned int levelNumber)
{
	os << "#level\n" << levelNumber << '\n' << '\n';
}

void LevelSaver::AddPossibleColours(const std::vector<glm::vec3>& colours)
{
	os << "#possible_colours\n";

	for (unsigned int i = 0; i < colours.size(); ++i)
	{
		os << colours[i].r << " " << colours[i].g << " " << colours[i].b << '\n';
	}

	os << '\n';
}

void LevelSaver::AddCubes(std::vector<std::unique_ptr<Cube>>& cubes)
{
	//TODO: only save x, y, z coords, keep face data
	os << "#cubes\n";
	for (auto& cube : cubes)
	{
		auto& p = cube->GetPosition();
		os << p.x << " " << p.y << " " << p.z << '\n';
		for (unsigned int i = 0; i < 6; ++i)
			os << (cube->CheckFace(Face(i)) ? 1 : 0) << " ";

		os << '\n';

		for (unsigned int i = 0; i < 6; ++i)
			os << (cube->CheckFace(Face(i)) ? i : 0) << " ";

		os << '\n';
	}
}

void LevelSaver::AddLevelName(const std::string& name)
{
	std::fstream stream("Resources/Data/LevelList.data");

	std::string line;
	while (std::getline(stream, line))
	{
		if (line == name)
		{
			return;
		}
	}

	stream.clear();
	stream << name << '\n';

}