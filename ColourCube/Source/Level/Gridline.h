#ifndef GRIDLINE_H
#define GRIDLINE_H
#include <memory>
#include <vector>
#include "../Entity.h"

class Mesh;

class Gridline : public Entity
{
private:
	std::unique_ptr<Mesh> m_Mesh;

public:
	Gridline(unsigned int xCount, unsigned int zCount);
	~Gridline();

	void HandleEvents()		override {}
	void Update()			override {}

	Mesh* GetMesh();

private:
	std::vector<float> CreateVertices(int xCount, int zCount);
	std::vector<unsigned int> CreateIndices(unsigned int xCount, unsigned int yCount);

};

#endif