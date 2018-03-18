#pragma once
struct Character
{
public:
	int id;
	float xTextureCoord;
	float yTextureCoord;
	float xMaxTextureCoord;
	float yMaxTextureCoord;
	float xOffset;
	float yOffset;
	float xSize;
	float ySize;
	float xAdvance;
	Character(int id, float xTextureCoord, float yTextureCoord, float xMaxTextureCoord, float yMaxTextureCoord,
		float xOffset, float yOffset, float xSize, float ySize, float xAdvance)
		: id(id), xTextureCoord(xTextureCoord), yTextureCoord(yTextureCoord), xMaxTextureCoord(xMaxTextureCoord), yMaxTextureCoord(yMaxTextureCoord),
		xOffset(xOffset), yOffset(yOffset), xSize(xSize), ySize(ySize), xAdvance(xAdvance)
	{

	}
};