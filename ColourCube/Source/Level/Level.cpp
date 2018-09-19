#include "Level.h"
#include "../Mesh/Mesh.h"
#include "../Input/Mouse3D.h"
#include "LevelCreator.h"
#include <iostream>

Level::Level(const unsigned int levelNumber, std::unique_ptr<Input::Mouse3D> mouseInput)
	: m_MouseInput(std::move(mouseInput))
	, m_Mesh(nullptr), m_CurrentLevel(levelNumber)
{
	Init();
}

Level::Level(const unsigned int levelNumber, Level* oldLevel)
	: m_MouseInput(std::move(oldLevel->m_MouseInput))
	, m_Mesh(nullptr), m_CurrentLevel(levelNumber)
{
	Init();
}

Level::~Level()
{
}

void Level::Init()
{
	if (m_LevelName.find("Load") != std::string::npos)
	{
		std::string::iterator it = m_LevelName.begin();
		auto pos = m_LevelName.find("Load");
		if (pos != std::string::npos)
		{
			it += pos;
			m_LevelName.erase(it, it + 4);
		}
	}

	std::vector<unsigned int> strides = { 3, 3, 4 };

	LevelCreator loader(m_CurrentLevel);
	m_Mesh = std::make_unique<Mesh>(loader.GetVertices(), strides);
	m_LevelName = loader.GetLevelName();
	m_CurrentLevel = loader.GetLevelNumber();
	m_PossibleColours = loader.GetPossibleColours();
	m_Cubes = std::move(loader.GetCubes());

	CalculatePosition(loader.GetPosition());
	m_MouseInput->CalculateTargets(m_Cubes);
}

void Level::HandleEvents()
{
	m_MouseInput->HandleEvents();
}

void Level::Update()
{
	if (m_MouseInput)
		m_MouseInput->Update(*this);

	if (m_UpdateNeeded)
	{
		m_MouseInput->CalculateTargets(m_Cubes);
		UpdateVertices();
		CheckWin();
		m_UpdateNeeded = false;
	}
}

bool Level::CheckWin()
{
	if (m_Cubes.size() > 1 && !m_CubesMatch)
	{
		for (unsigned int i = 0; i < m_Cubes.size() - 1; ++i)
		{
			if (*m_Cubes[i].get() != *m_Cubes[i + 1].get())
			{
				return false;
			}
		}
		m_CubesMatch = true;
		return true;
	}
	return false;
}

void Level::Undo()
{
	if (!m_PastMoves.empty())
	{
		auto type = m_PastMoves.back().first;
		auto move = m_PastMoves.back().second;
		if (type == MOVE_TYPE::ADD)
		{
			RemoveCube(move.x, move.y, move.z);
		}
		if (type == MOVE_TYPE::REMOVE)
		{
			AddCube(move.x, move.y, move.z);
		}
		RemoveMove(type, move.x, move.y, move.z);
		m_PastMoves.pop_back();
	}
}

void Level::Redo()
{
	if (!m_FutureMoves.empty())
	{
		auto type = m_FutureMoves.back().first;
		auto move = m_FutureMoves.back().second;
		if (type == MOVE_TYPE::ADD)
		{
			AddCube(move.x, move.y, move.z);
		}
		if (type == MOVE_TYPE::REMOVE)
		{
			RemoveCube(move.x, move.y, move.z);
		}
		m_FutureMoves.pop_back();
		m_PastMoves.emplace_back(type, move);
	}
}

void Level::AddMove(MOVE_TYPE type, float x, float y, float z)
{
	m_PastMoves.emplace_back(type, glm::vec3{ x, y, z });
	if (m_PastMoves.size() >= MAX_SAVED_MOVES)
		m_PastMoves.erase(m_PastMoves.begin());
	if (!m_FutureMoves.empty())
		m_FutureMoves.clear();
}

void Level::RemoveMove(MOVE_TYPE type, float x, float y, float z)
{
	m_FutureMoves.emplace_back(type, glm::vec3{ x, y, z });
}

Cube* Level::AddCube(float x, float y, float z)
{
	for (auto& cube : m_Cubes)
	{
		if (cube->GetPosition() == glm::vec3{ x, y, z })
		{
			return nullptr;
		}
	}

	std::unordered_map<Face, short> sides;
	sides.insert({
		{ Face::TOP,	0 },
		{ Face::BOTTOM, 0 },
		{ Face::NORTH,	0 },
		{ Face::EAST,	0 },
		{ Face::SOUTH,	0 },
		{ Face::WEST,	0 }
	});

	auto& newCube = std::make_unique<Cube>(sides, m_PossibleColours, x, y, z);

	m_Cubes.emplace_back(std::move(newCube));
	m_UpdateNeeded = true;
	return m_Cubes.back().get();
}

Cube* Level::GetCube(float x, float y, float z)
{
	for (auto& cube : m_Cubes)
	{
		if (cube->GetPosition() == glm::vec3{ x, y, z })
		{
			std::swap(cube, m_Cubes.back());
			return m_Cubes.back().get();
		}
	}
	return nullptr;
}

void Level::RemoveCube(float x, float y, float z)
{
	for (auto& cube = m_Cubes.begin(); cube != m_Cubes.end();)
	{
		auto& pos = cube->get()->GetPosition();
		if (pos.x == x && pos.y == y && pos.z == z)
		{
			FillFaces(pos.x, pos.y, pos.z);
			m_Cubes.erase(cube);
			m_UpdateNeeded = true;
			return;
		}
		++cube;
	}
}

void Level::FillFaces(float x, float y, float z)
{
	for (auto& cube : m_Cubes)
	{
		auto& pos = cube->GetPosition();

		if (x - 1 == pos.x && y == pos.y && z == pos.z)
		{
			cube->AddFace(Face::EAST);
		}
		if (x + 1 == pos.x && y == pos.y && z == pos.z)
		{
			cube->AddFace(Face::WEST);
		}
		if (y - 1 == pos.y && z == pos.z && x == pos.x)
		{
			cube->AddFace(Face::TOP);
		}
		if (y + 1 == pos.y && z == pos.z && x == pos.x)
		{
			cube->AddFace(Face::BOTTOM);
		}
		if (z - 1 == pos.z && x == pos.x && y == pos.y)
		{
			cube->AddFace(Face::SOUTH);
		}
		if (z + 1 == pos.z && x == pos.x && y == pos.y)
		{
			cube->AddFace(Face::NORTH);
		}

	}
	m_UpdateNeeded = true;
}

void Level::RemoveFaces(Cube* cube)
{
	auto& p1 = cube->GetPosition();
	for (auto& curCube : m_Cubes)
	{
		auto& p2 = curCube->GetPosition();
		if (abs(p2.x - p1.x) > 1.0f || abs(p2.y - p1.y) > 1.0f || abs(p2.z - p1.z) > 1.0f)
		{
			continue;
		}

		if (p2.x - 1 == p1.x && p2.y == p1.y && p2.z == p1.z)
		{
			curCube->RemoveFace(Face::WEST);
			cube->RemoveFace(Face::EAST);
		}
		if (p2.x + 1 == p1.x && p2.y == p1.y && p2.z == p1.z)
		{
			curCube->RemoveFace(Face::EAST);
			cube->RemoveFace(Face::WEST);
		}
		if (p2.y - 1 == p1.y && p2.x == p1.x && p2.z == p1.z)
		{
			curCube->RemoveFace(Face::BOTTOM);
			cube->RemoveFace(Face::TOP);
		}
		if (p2.y + 1 == p1.y && p2.x == p1.x && p2.z == p1.z)
		{
			curCube->RemoveFace(Face::TOP);
			cube->RemoveFace(Face::BOTTOM);
		}
		if (p2.z - 1 == p1.z && p2.y == p1.y && p2.x == p1.x)
		{
			curCube->RemoveFace(Face::NORTH);
			cube->RemoveFace(Face::SOUTH);
		}
		if (p2.z + 1 == p1.z && p2.y == p1.y && p2.x == p1.x)
		{
			curCube->RemoveFace(Face::SOUTH);
			cube->RemoveFace(Face::NORTH);
		}

	}
	m_UpdateNeeded = true;
}

void Level::ToggleMode(MOVE_TYPE type)
{
	if (type == MOVE_TYPE::PLACE)
	{
		m_MouseInput->ToggleMode();
	}
}

void Level::ChangeMouseInput(std::unique_ptr<Input::Mouse3D> mouseInput)
{
	m_MouseInput = std::move(mouseInput);
	m_MouseInput->CalculateTargets(m_Cubes);
}

void Level::AddColour(glm::vec3& colour)
{
	m_PossibleColours.emplace_back(colour);

	for (auto& cube : m_Cubes)
	{
		cube->AddColour(m_PossibleColours);
	}
}

void Level::RemoveColours()
{
	m_PossibleColours.clear();
	m_PossibleColours.emplace_back(glm::vec3{ 1.0f, 1.0f, 1.0f }); //Default colour

	for (auto& cube : m_Cubes)
	{
		cube->RemoveColours();
		cube->AddColour(m_PossibleColours);
	}

	m_UpdateNeeded = true;
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

	m_UpdateNeeded = true;
}

void Level::ForceUpdate()
{
	m_UpdateNeeded = true;
}

Mesh* Level::GetMesh()
{
	return m_Mesh.get();
}

void Level::UpdateVertices()
{
	std::vector<float> vertices;
	for (auto& cube : m_Cubes)
	{
		auto& cubeVertices = cube->GetVertices();
		vertices.insert(vertices.end(), cubeVertices.begin(), cubeVertices.end());
	}
	m_Mesh->UpdateVertices(vertices, 10);
}

void Level::CalculatePosition(glm::vec3& inPosition)
{
	m_Position.x = inPosition.x / 2.0f;
	m_Position.y = inPosition.y / 2.0f;
	m_Position.z = inPosition.z / 2.0f;
}

bool Level::CubeFaceExists(int x, int y, int z, Face face)
{	
	for (auto& cube : m_Cubes)
	{
		auto& position = cube->GetPosition();
		if ((int)position.x == x && (int)position.y == y && (int)position.z == z)
		{
			if (cube->CheckFace(face))
			{
				cube->ChangeColour(face);
				m_UpdateNeeded = true;
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
