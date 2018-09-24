#include "LevelSaver.h"
#include <string>
#include "Level.h"

LevelSaver::LevelSaver(Level* level)
{
	const std::string file = "Resources/Data/" + level->GetLevelName() + ".xml";

	os.open(file);

	os << "<Level>\n";
	AddLevelName(level->GetLevelName());
	AddPossibleColours(level->GetPossibleColours());
	AddCubes(level->GetCubes());
	os << "</Level>\n";

	os.close();

	AddToLevelList(level->GetLevelName());

}

void LevelSaver::AddLevelName(const std::string& name)
{
	os << "  <Name>" << name << "</Name>\n";
}

void LevelSaver::AddPossibleColours(const std::vector<glm::vec3>& colours)
{
	os << "  <Colours>\n";

	for (unsigned int i = 0; i < colours.size(); ++i)
	{
		os << "    <colour>" << colours[i].r << " " << colours[i].g << " " << colours[i].b << "</colour>\n";
	}

	os << "  </Colours>\n";
}

void LevelSaver::AddCubes(std::vector<std::unique_ptr<Cube>>& cubes)
{
	os << "  <Cubes>\n";

	for (auto& cube : cubes)
	{
		os << "    <cube>\n";

		auto& p = cube->position;
		os << "      <position>" << p.x << " " << p.y << " " << p.z << "</position>\n";

		os << "      <faces>";
		for (unsigned int i = 0; i < 6; ++i)
		{
			os << (cube->CheckFace(Face(i)) ? 1 : 0);

			if (i < 5)
			{
				os << " ";
			}
		}
		os << "</faces>\n";

		os << "      <stage>";

		auto& sides = cube->GetSides();
		for (unsigned int i = 0; i < 6; ++i)
		{
			if (sides.find(Face(i)) != sides.end())
			{
				os << sides.at(Face(i));
			}
			else
			{
				os << "0";
			}

			if (i < 5)
				os << " ";
		}

		os << "</stage>\n";

		os << "    </cube>\n";
	}

	os << "  </Cubes>\n";
}


void LevelSaver::AddToLevelList(const std::string& name)
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

	stream.close();
}