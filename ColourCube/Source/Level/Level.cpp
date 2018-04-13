#include "Level.h"
#include <iostream>

#include "../Mesh/Mesh.h"
#include "../Input/InputBase.h"
#include "../Input/MousePicker.h"
#include "LevelCreator.h"

Level::Level(std::unique_ptr<Input::InputBase> keyInput, std::unique_ptr<Input::MousePicker> mouseInput)
	: m_Position({ 0.0f, 0.0f, 0.0f }), m_Mesh(nullptr)
	, m_KeyInput(std::move(keyInput)), m_MouseInput(std::move(mouseInput))
	, m_CurrentLevel(0)
{
	LevelCreator loader("Level.data");
	m_Mesh = std::make_unique<Mesh>(loader.GetVertices(), 3, 3);
	m_CurrentLevel = loader.GetLevelNumber();
	m_CubeKey = loader.GetCubeKey();
	m_Cubes = loader.GetCubes();

	CalculatePosition();
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
		ChangeColour((int)UpdateCoords.x, (int)UpdateCoords.y, (int)UpdateCoords.z, Face::SOUTH);
		break;
	case Command::CHANGE_COLOUR_2:
		ChangeColour(1, 0, 1, Face::EAST);
		break;
	}
}

void Level::Draw() const
{
	Bind();
	glDrawElements(GL_TRIANGLES, m_Mesh->GetCount(), GL_UNSIGNED_INT, nullptr);
	Unbind();
}

void Level::Bind() const
{
	m_Mesh->Bind();
}

void Level::Unbind() const
{
	m_Mesh->Unbind();
}

void Level::UpdateVertices()
{
	std::vector<float> vertices;
	for (Cube& cube : m_Cubes)
	{
		auto& cubeVertices = cube.GetSides();
		vertices.insert(vertices.end(), cubeVertices.begin(), cubeVertices.end());
	}

	m_Mesh->UpdateVertices(vertices);
}

void Level::CalculatePosition()
{
	//TODO: Calculate based on average of all rows/columns
	m_Position.x = m_CubeKey[0][0] / 2.0f;
	m_Position.y = m_CubeKey.size() / 2.0f;
	m_Position.z = m_CubeKey[0].size() / 2.0f;
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
		if (!CubeFaceExists(x, y, z, Face::NORTH))
			if (!CubeFaceExists(x, y, z - 1, face))
				CubeFaceExists(x, y + 1, z - 1, Face::SOUTH);

		if (!CubeFaceExists(x, y, z, Face::EAST))
			if (!CubeFaceExists(x + 1, y, z, face))
				CubeFaceExists(x + 1, y + 1, z, Face::WEST);

		if (!CubeFaceExists(x, y, z, Face::SOUTH))
			if (!CubeFaceExists(x, y, z + 1, face))
				CubeFaceExists(x, y + 1, z + 1, Face::NORTH);

		if (!CubeFaceExists(x, y, z, Face::WEST))
			if (!CubeFaceExists(x - 1, y, z, face))
				CubeFaceExists(x - 1, y + 1, z, Face::EAST);
	}
		break;
	case Face::NORTH: {
		if (!CubeFaceExists(x, y, z, Face::TOP))
			if (!CubeFaceExists(x, y + 1, z, face))
				CubeFaceExists(x, y + 1, z - 1, Face::BOTTOM);

		if (!CubeFaceExists(x, y, z, Face::BOTTOM))
			if (!CubeFaceExists(x, y - 1, z, face))
				CubeFaceExists(x, y - 1, z - 1, Face::TOP);

		if (!CubeFaceExists(x, y, z, Face::WEST))
			if (!CubeFaceExists(x - 1, y, z, face))
				CubeFaceExists(x - 1, y, z - 1, Face::EAST);

		if (!CubeFaceExists(x, y, z, Face::EAST))
			if (!CubeFaceExists(x + 1, y, z, face))
				CubeFaceExists(x + 1, y, z - 1, Face::EAST);
	}
		break;
	case Face::EAST: { 
		if (!CubeFaceExists(x, y, z, Face::TOP))
			if (!CubeFaceExists(x, y + 1, z, face))
				CubeFaceExists(x + 1, y + 1, z, Face::BOTTOM);

		if (!CubeFaceExists(x, y, z, Face::BOTTOM))
			if (!CubeFaceExists(x, y - 1, z, face))
				CubeFaceExists(x + 1, y - 1, z, Face::TOP);

		if (!CubeFaceExists(x, y, z, Face::NORTH))
			if (!CubeFaceExists(x, y, z - 1, face))
				CubeFaceExists(x + 1, y, z - 1, Face::SOUTH);

		if (!CubeFaceExists(x, y, z, Face::SOUTH))
			if (!CubeFaceExists(x, y, z + 1, face))
				CubeFaceExists(x + 1, y, z + 1, Face::NORTH);
	}
		break;
	case Face::SOUTH: {
		if (!CubeFaceExists(x, y, z, Face::TOP))
			if (!CubeFaceExists(x, y + 1, z, face))
				CubeFaceExists(x, y + 1, z + 1, Face::BOTTOM);

		if (!CubeFaceExists(x, y, z, Face::BOTTOM))
			if (!CubeFaceExists(x, y - 1, z, face))
				CubeFaceExists(x, y - 1, z + 1, Face::TOP);

		if (!CubeFaceExists(x, y, z, Face::WEST))
			if (!CubeFaceExists(x - 1, y, z, face))
				CubeFaceExists(x - 1, y, z + 1, Face::EAST);

		if (!CubeFaceExists(x, y, z, Face::EAST))
			if (!CubeFaceExists(x + 1, y, z, face))
				CubeFaceExists(x - 1, y, z - 1, Face::WEST);
	}
		break;
	case Face::WEST: {
		if (!CubeFaceExists(x, y, z, Face::TOP))
			if (!CubeFaceExists(x, y + 1, z, face))
				CubeFaceExists(x - 1, y + 1, z, Face::BOTTOM);

		if (!CubeFaceExists(x, y, z, Face::BOTTOM))
			if (!CubeFaceExists(x, y - 1, z, face))
				CubeFaceExists(x - 1, y - 1, z, Face::TOP);

		if (!CubeFaceExists(x, y, z, Face::NORTH))
			if (!CubeFaceExists(x, y, z - 1, face))
				CubeFaceExists(x - 1, y, z - 1, Face::SOUTH);

		if (!CubeFaceExists(x, y, z, Face::SOUTH))
			if (!CubeFaceExists(x, y, z + 1, face))
				CubeFaceExists(x - 1, y, z - 1, Face::NORTH);
	}
		break;
	case Face::BOTTOM: {
		if (!CubeFaceExists(x, y, z, Face::NORTH))
			if (!CubeFaceExists(x, y, z - 1, face))
				CubeFaceExists(x, y - 1, z - 1, Face::SOUTH);

		if (!CubeFaceExists(x, y, z, Face::EAST))
			if (!CubeFaceExists(x + 1, y, z, face))
				CubeFaceExists(x + 1, y - 1, z, Face::WEST);
		
		if (!CubeFaceExists(x, y, z, Face::SOUTH))
			if (!CubeFaceExists(x, y, z + 1, face))
				CubeFaceExists(x, y - 1, z + 1, Face::NORTH);

		if (!CubeFaceExists(x, y, z, Face::WEST))
			if (!CubeFaceExists(x - 1, y, z, face))
				CubeFaceExists(x - 1, y - 1, z, Face::EAST);
	}
		break;
	default: std::cout << "Face doesn't exist" << std::endl;
		return;
	}

	m_Updated = true;
}

bool Level::CubeFaceExists(int x, int y, int z, Face face)
{	
	if (x < 0 || y < 0 || z < 0)
		return false;

	if ((unsigned int)y >= m_CubeKey.size() || (unsigned int)z >= m_CubeKey[y].size() || (unsigned int)x > m_CubeKey[y][z])
	{
		std::cout << m_CubeKey[y].size() << std::endl;
		return false;
	}
	
	int index = 0;
	for (int i = 0; i < y; i++)
		for (unsigned int j = 0; j < m_CubeKey[i].size(); j++)
			index += m_CubeKey[i][j];

	index += (z * m_CubeKey[y].size()) + x;

	if (m_Cubes[index].CheckFace(face))
		m_Cubes[index].ChangeColour(face);
	else
		return false;

	return true;
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