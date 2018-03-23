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
	/*Character(int id, float xTextureCoord, float yTextureCoord, float xMaxTextureCoord, float yMaxTextureCoord,
		float xOffset, float yOffset, float xSize, float ySize, float xAdvance)
		: id(id), xTextureCoord(xTextureCoord), yTextureCoord(yTextureCoord), xMaxTextureCoord(xMaxTextureCoord), yMaxTextureCoord(yMaxTextureCoord),
		xOffset(xOffset), yOffset(yOffset), xSize(xSize), ySize(ySize), xAdvance(xAdvance)
	{

	}*/

	Character(int id = 0, float xTextureCoord = 0.0f, float yTextureCoord = 0.0f, float xMaxTextureCoord = 0.0f, float yMaxTextureCoord = 0.0f,
		float xOffset = 0.0f, float yOffset = 0.0f, float xSize = 0.0f, float ySize = 0.0f, float xAdvance = 0.0f)
		: id(id), xTextureCoord(xTextureCoord), yTextureCoord(yTextureCoord), xMaxTextureCoord(xMaxTextureCoord), yMaxTextureCoord(yMaxTextureCoord),
		xOffset(xOffset), yOffset(yOffset), xSize(xSize), ySize(ySize), xAdvance(xAdvance)
	{

	}

	bool operator==(const Character& rhs)
	{
		if (id = rhs.id)
			return true;

		return false;
	}
};