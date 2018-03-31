#ifndef CHARACTER_H
#define CHARACTER_H

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

	Character(int id = 0, float xTexCoord = 0.0f, float yTexCoord = 0.0f, float xTexSize = 0.0f, float yTexSize = 0.0f,
		float xOffset = 0.0f, float yOffset = 0.0f, float xSize = 0.0f, float ySize = 0.0f, float xAdvance = 0.0f)
		: id(id), xTextureCoord(xTexCoord), yTextureCoord(yTexCoord), xSize(xSize), ySize(ySize)
		, xMaxTextureCoord(xTexSize + xTexCoord), yMaxTextureCoord(yTexCoord - yTexSize)
		, xOffset(xOffset), yOffset(yOffset), xAdvance(xAdvance)
	{
		
	}

	bool operator==(const Character& rhs)
	{
		if (id == rhs.id)
			return true;

		return false;
	}
};

#endif