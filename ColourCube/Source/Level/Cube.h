#ifndef CUBE_H
#define CUBE_H
#include <vector>
#include <unordered_map>
#include "GLM/glm.hpp"

enum class Face {
	TOP		= 0,
	NORTH	= 1,
	EAST	= 2,
	SOUTH	= 3,
	WEST	= 4,
	BOTTOM	= 5
};

class Cube
{
private:
	float m_Size = 0.5f;
	glm::vec3 m_Position;
	std::vector<float> m_Vertices;
	std::vector<glm::vec3> m_Colours;
	glm::vec3* m_HighlightColour;
	float m_Alpha;
	std::unordered_map<Face, int> m_Sides;
	bool m_Ghost = false;

public:
	Cube(const std::unordered_map<Face, int>& sides, std::vector<glm::vec3>& colours, float x = 0, float y = 0, float z = 0);
	~Cube();

	void ChangeColour(Face face);
	bool CheckFace(Face face);

	void AddFace(Face face, int colour = 0);
	void AddFace(const std::pair<Face, int>& side);
	void RemoveFace(Face face);

	Cube* SetGhost(bool ghost = true);
	Cube* SetAlpha(float alpha);
	Cube* SetColour(float r, float g, float b);
	Cube* SetHighlightColour(glm::vec3* colour);

	const std::vector<float>& GetVertices();
	inline const auto& GetPosition()			{ return m_Position; }
	inline const auto& GetSides()				{ return m_Sides; }
	inline auto& IsGhost()						{ return m_Ghost; }

	bool operator==(const Cube& rhs);
	bool operator!=(const Cube& rhs);

private:
	void CalculateVertices();
};

#endif