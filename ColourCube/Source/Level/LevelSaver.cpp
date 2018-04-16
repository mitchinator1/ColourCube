#include "LevelSaver.h"
#include <iostream>
#include <string>
#include "Level.h"
#include "Cube.h"

LevelSaver::LevelSaver(Level* level)
{
	std::ofstream os("Resources/Data/TestFile.data");

	AddLevelNumber(os, level->GetCurrentLevel());
	AddRows(os, level->GetCubeKey());
	AddPossibleColours(os, level->GetPossibleColours());
	AddCubes(os, level->GetCubes());

	os.close();

	std::cout << "Level saved" << std::endl;
}

void LevelSaver::AddLevelNumber(std::ofstream& os, const unsigned int levelNumber)
{
	os << "#level\n" << levelNumber << '\n' << '\n';
}

void LevelSaver::AddRows(std::ofstream& os, const std::vector<std::vector<unsigned int>>& rows)
{
	os << "#rows\n";

	for (unsigned int i = 0; i < rows.size(); ++i)
	{
		for (unsigned int j = 0; j < rows[i].size(); ++j)
		{
			os << rows[i][j] << " ";
		}
		os << '\n';
	}
	os << '\n';
}

void LevelSaver::AddPossibleColours(std::ofstream& os, const std::vector<Colour> colours)
{
	os << "#possible_colours\n";

	for (unsigned int i = 0; i < colours.size(); ++i)
	{
		os << colours[i].r << " " << colours[i].g << " " << colours[i].b << '\n';
	}

	os << '\n';
}

void LevelSaver::AddCubes(std::ofstream& os, std::vector<Cube>& cubes)
{
	os << "#cubes\n";
	for (auto& cube : cubes)
	{
		auto& p = cube.GetPosition();
		os << p.x << " " << p.y << " " << p.z << '\n';
		for (unsigned int i = 0; i < 6; ++i)
			os << (cube.CheckFace(Face(i)) ? 1 : 0) << " ";

		os << '\n';

		for (unsigned int i = 0; i < 6; ++i)
			os << (cube.CheckFace(Face(i)) ? cube.GetSide(Face(i)).currentColour : 0) << " ";

		os << '\n' << '\n';
	}
}