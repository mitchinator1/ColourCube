#pragma once
#include <vector>

namespace Text
{
	class TextMeshData {
	private:
		std::vector<float> m_VertexPositions;
		std::vector<float> m_TextureCoords;

	public:
		TextMeshData(std::vector<float>& vertexPositions, std::vector<float>& textureCoords);

		std::vector<float>& GetVertexPositions();
		std::vector<float>& GetTextureCoords();
	};
}