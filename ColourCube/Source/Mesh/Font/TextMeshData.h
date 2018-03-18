#pragma once
#include <vector>

class TextMeshData {
private:
	std::vector<float> m_VertexPositions;
	std::vector<float> m_TextureCoords;

public:
	TextMeshData(std::vector<float>& vertexPositions, std::vector<float>& textureCoords)
		: m_VertexPositions(vertexPositions), m_TextureCoords(textureCoords)
	{

	}

	std::vector<float>& GetVertexPositions()
	{
		return m_VertexPositions;
	}

	std::vector<float>& GetTextureCoords()
	{
		return m_TextureCoords;
	}

	int GetVertexCount()
	{
		return m_VertexPositions.size() / 2;
	}

};