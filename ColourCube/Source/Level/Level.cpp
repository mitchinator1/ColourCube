#include "Level.h"
#include <iostream>

#include "../Input/InputBase.h"
#include "../Input/MouseBase.h"

#include "LevelCreator.h"

Level::Level(const std::string& levelName, std::unique_ptr<Input::InputBase> keyInput, std::unique_ptr<Input::MouseBase> mouseInput)
	: m_LevelName(levelName), m_KeyInput(std::move(keyInput)), m_MouseInput(std::move(mouseInput))
	, m_Mesh(nullptr), m_CurrentLevel(0)
{
	LevelCreator loader(levelName + ".data");
	m_Mesh = std::make_unique<Mesh>(loader.GetVertices(), 3, 3);
	m_CurrentLevel = loader.GetLevelNumber();
	m_PossibleColours = loader.GetPossibleColours();
	m_Cubes = loader.GetCubes();
	
	CalculatePosition(loader.GetPosition());
}

Level::~Level()
{
	
}

void Level::HandleEvents()
{
	m_KeyInput->HandleEvents(*this);
	m_MouseInput->HandleEvents();
}

void Level::Update()
{
	m_Updated = false;
	
	m_KeyInput->Update(*this);
	m_MouseInput->Update(*this);

	if (m_Updated)
	{
		UpdateVertices();
	}
}

void Level::Action(Command command)
{
	switch (command)
	{
	case Command::CHANGE_COLOUR:
		//ChangeColour((int)UpdateCoords.x, (int)UpdateCoords.y, (int)UpdateCoords.z, Face::SOUTH);
		break;
	}
}
 
void Level::Bind() const
{
	m_Mesh->Bind();
}

void Level::Unbind() const
{
	m_Mesh->Unbind();
}

bool Level::CheckWin()
{
	if (m_Updated)
	{
		for (unsigned int i = 0; i < m_Cubes.size() - 1; ++i)
			if (m_Cubes[i] != m_Cubes[i + 1])
				return false;

		return true;
	}
	return false;
}

void Level::AddCube(float x, float y, float z)
{
	std::vector<Side> sides = {
		Side{ Face::TOP },
		Side{ Face::BOTTOM },
		Side{ Face::NORTH },
		Side{ Face::EAST },
		Side{ Face::SOUTH },
		Side{ Face::WEST }
	};

	Cube newCube(sides, m_PossibleColours, x, y, z);

	for (auto& curCube : m_Cubes)
	{
		auto& position = curCube.GetPosition();
		if (position.x - 1 == x && position.y == y && position.z == z)
		{
			curCube.RemoveSide(Side{ Face::WEST });
			newCube.RemoveSide(Side{ Face::EAST });
		}
		if (position.x + 1 == x && position.y == y && position.z == z)
		{
			curCube.RemoveSide(Side{ Face::EAST });
			newCube.RemoveSide(Side{ Face::WEST });
		}
		if (position.y + 1 == y && position.x == x && position.z == z)
		{
			curCube.RemoveSide(Side{ Face::TOP });
			newCube.RemoveSide(Side{ Face::BOTTOM });
		}
		if (position.y - 1 == y && position.x == x && position.z == z)
		{
			curCube.RemoveSide(Side{ Face::BOTTOM });
			newCube.RemoveSide(Side{ Face::TOP });
		}
		if (position.z - 1 == z && position.y == y && position.x == x)
		{
			curCube.RemoveSide(Side{ Face::NORTH });
			newCube.RemoveSide(Side{ Face::SOUTH });
		}
		if (position.z + 1 == z && position.y == y && position.x == x)
		{
			curCube.RemoveSide(Side{ Face::SOUTH });
			newCube.RemoveSide(Side{ Face::NORTH });
		}
	}

	m_Cubes.emplace_back(newCube);
	
	std::vector<float> vertices;
	for (Cube& cube : m_Cubes)
	{
		auto& cubeVertices = cube.GetVertices();
		vertices.insert(vertices.end(), cubeVertices.begin(), cubeVertices.end());
	}
	m_Mesh = std::make_unique<Mesh>(vertices, 3, 3);
}

void Level::RemoveCube(float x, float y, float z)
{
	bool found = false;
	int index;

	for (unsigned int i = 0; i < m_Cubes.size(); ++i)
	{
		auto& cube = m_Cubes[i].GetPosition();
		if (cube.x == x && cube.y == y && cube.z == z)
		{
			found = true;
			index = i;
		}
		
		if (cube.x - 1 == x && cube.y == y && cube.z == z)
			{
				m_Cubes[i].AddSide(Side{ Face::WEST });
			}
		if (cube.x + 1 == x && cube.y == y && cube.z == z)
			{
				m_Cubes[i].AddSide(Side{ Face::EAST });
			}
		if (cube.y + 1 == y && cube.x == x && cube.z == z)
			{
				m_Cubes[i].AddSide(Side{ Face::TOP });
			}
		if (cube.y - 1 == y && cube.x == x && cube.z == z)
			{
				m_Cubes[i].AddSide(Side{ Face::BOTTOM });
			}
		if (cube.z - 1 == z && cube.y == y && cube.x == x)
			{
				m_Cubes[i].AddSide(Side{ Face::NORTH });
			}
		if (cube.z + 1 == z && cube.y == y && cube.x == x)
			{
				m_Cubes[i].AddSide(Side{ Face::SOUTH });
			}
	}
	if (found)
	{
		m_Cubes.erase(m_Cubes.begin() + index);

		std::vector<float> vertices;
		for (Cube& cube : m_Cubes)
		{
			auto& cubeVertices = cube.GetVertices();
			vertices.insert(vertices.end(), cubeVertices.begin(), cubeVertices.end());
		}
		m_Mesh = std::make_unique<Mesh>(vertices, 3, 3);
	}
}

bool Level::ToggleMode()
{
	return m_MouseInput->ToggleMode();
}

void Level::AddColour(glm::vec3& colour)
{
	m_PossibleColours.emplace_back(Colour{ colour.r, colour.g, colour.b });
}

void Level::ChangeColour(int x, int y, int z, Face face)
{
	if (!CubeFaceExists(x, y, z, face))
	{
		std::cout << "Face doesn't exist at [" << x << "][" << y << "][" << z << "]!" << std::endl;
		return;
	}

	switch (face)
	{
	case Face::TOP: {
		if (!CubeFaceExists(x, y + 1, z - 1, Face::SOUTH))
			if (!CubeFaceExists(x, y, z - 1, face))
				CubeFaceExists(x, y, z, Face::NORTH);

		if (!CubeFaceExists(x + 1, y + 1, z, Face::WEST))
			if (!CubeFaceExists(x + 1, y, z, face))
				CubeFaceExists(x, y, z, Face::EAST);

		if (!CubeFaceExists(x, y + 1, z + 1, Face::NORTH))
			if (!CubeFaceExists(x, y, z + 1, face))
				CubeFaceExists(x, y, z, Face::SOUTH);

		if (!CubeFaceExists(x - 1, y + 1, z, Face::EAST))
			if (!CubeFaceExists(x - 1, y, z, face))
				CubeFaceExists(x, y, z, Face::WEST);
	}
		break;
	case Face::NORTH: {
		if (!CubeFaceExists(x, y + 1, z - 1, Face::BOTTOM))
			if (!CubeFaceExists(x, y + 1, z, face))
				CubeFaceExists(x, y, z, Face::TOP);

		if (!CubeFaceExists(x, y - 1, z - 1, Face::TOP))
			if (!CubeFaceExists(x, y - 1, z, face))
				CubeFaceExists(x, y, z, Face::BOTTOM);

		if (!CubeFaceExists(x - 1, y, z - 1, Face::EAST))
			if (!CubeFaceExists(x - 1, y, z, face))
				CubeFaceExists(x, y, z, Face::WEST);

		if (!CubeFaceExists(x + 1, y, z - 1, Face::WEST))
			if (!CubeFaceExists(x + 1, y, z, face))
				CubeFaceExists(x, y, z, Face::EAST);
	}
		break;
	case Face::EAST: { 
		if (!CubeFaceExists(x + 1, y + 1, z, Face::BOTTOM))
			if (!CubeFaceExists(x, y + 1, z, face))
				CubeFaceExists(x, y, z, Face::TOP);

		if (!CubeFaceExists(x + 1, y - 1, z, Face::TOP))
			if (!CubeFaceExists(x, y - 1, z, face))
				CubeFaceExists(x, y, z, Face::BOTTOM);

		if (!CubeFaceExists(x + 1, y, z - 1, Face::SOUTH))
			if (!CubeFaceExists(x, y, z - 1, face))
				CubeFaceExists(x, y, z, Face::NORTH);

		if (!CubeFaceExists(x + 1, y, z + 1, Face::NORTH))
			if (!CubeFaceExists(x, y, z + 1, face))
				CubeFaceExists(x, y, z, Face::SOUTH);
	}
		break;
	case Face::SOUTH: {
		if (!CubeFaceExists(x, y + 1, z + 1, Face::BOTTOM))
			if (!CubeFaceExists(x, y + 1, z, face))
				CubeFaceExists(x, y, z, Face::TOP);

		if (!CubeFaceExists(x, y - 1, z + 1, Face::TOP))
			if (!CubeFaceExists(x, y - 1, z, face))
				CubeFaceExists(x, y, z, Face::BOTTOM);

		if (!CubeFaceExists(x - 1, y, z + 1, Face::EAST))
			if (!CubeFaceExists(x - 1, y, z, face))
				CubeFaceExists(x, y, z, Face::WEST);

		if (!CubeFaceExists(x + 1, y, z + 1, Face::WEST))
			if (!CubeFaceExists(x + 1, y, z, face))
				CubeFaceExists(x, y, z, Face::EAST);
	}
		break;
	case Face::WEST: {
		if (!CubeFaceExists(x - 1, y + 1, z, Face::BOTTOM))
			if (!CubeFaceExists(x, y + 1, z, face))
				CubeFaceExists(x, y, z, Face::TOP);

		if (!CubeFaceExists(x - 1, y - 1, z, Face::TOP))
			if (!CubeFaceExists(x, y - 1, z, face))
				CubeFaceExists(x, y, z, Face::BOTTOM);

		if (!CubeFaceExists(x - 1, y, z - 1, Face::SOUTH))
			if (!CubeFaceExists(x, y, z - 1, face))
				CubeFaceExists(x, y, z, Face::NORTH);

		if (!CubeFaceExists(x - 1, y, z + 1, Face::NORTH))
			if (!CubeFaceExists(x, y, z + 1, face))
				CubeFaceExists(x, y, z, Face::SOUTH);
	}
		break;
	case Face::BOTTOM: {
		if (!CubeFaceExists(x, y - 1, z - 1, Face::SOUTH))
			if (!CubeFaceExists(x, y, z - 1, face))
				CubeFaceExists(x, y, z, Face::NORTH);

		if (!CubeFaceExists(x + 1, y - 1, z, Face::WEST))
			if (!CubeFaceExists(x + 1, y, z, face))
				CubeFaceExists(x, y, z, Face::EAST);
		
		if (!CubeFaceExists(x, y - 1, z + 1, Face::NORTH))
			if (!CubeFaceExists(x, y, z + 1, face))
				CubeFaceExists(x, y, z, Face::SOUTH);

		if (!CubeFaceExists(x - 1, y - 1, z, Face::EAST))
			if (!CubeFaceExists(x - 1, y, z, face))
				CubeFaceExists(x, y, z, Face::WEST);
	}
		break;
	default: std::cout << "Face doesn't exist" << std::endl;
		return;
	}

	m_Updated = true;
}

void Level::UpdateVertices()
{
	std::vector<float> vertices;
	for (Cube& cube : m_Cubes)
	{
		auto& cubeVertices = cube.GetVertices();
		vertices.insert(vertices.end(), cubeVertices.begin(), cubeVertices.end());
	}

	m_Mesh->UpdateVertices(vertices);
}

void Level::CalculatePosition(glm::vec3& inPosition)
{
	//TODO: Calculate based on average of all rows/columns
	m_Position.x = inPosition.x / 2.0f;
	m_Position.y = inPosition.y / 2.0f;
	m_Position.z = inPosition.z / 2.0f;
}

bool Level::CubeFaceExists(int x, int y, int z, Face face)
{	
	for (auto& cube : m_Cubes)
	{
		auto& position = cube.GetPosition();
		if ((int)position.x == x && (int)position.y == y && (int)position.z == z)
		{
			if (cube.CheckFace(face))
			{
				cube.ChangeColour(face);
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	return false;
}