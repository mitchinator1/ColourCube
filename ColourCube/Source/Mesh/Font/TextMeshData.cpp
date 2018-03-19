#include "TextMeshData.h"

namespace Text
{
	TextMeshData::TextMeshData(std::vector<float>& vertexPositions, std::vector<float>& textureCoords)
		: m_VertexPositions(vertexPositions), m_TextureCoords(textureCoords)
	{

	}

	std::vector<float>& TextMeshData::GetVertexPositions()
	{
		return m_VertexPositions;
	}

	std::vector<float>& TextMeshData::GetTextureCoords()
	{
		return m_TextureCoords;
	}

	int TextMeshData::GetVertexCount()
	{
		return m_VertexPositions.size() / 2;
	}
}