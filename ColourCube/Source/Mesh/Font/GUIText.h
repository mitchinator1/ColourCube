#pragma once
#include "GLM/glm.hpp"
#include <string>

//#include "FontType.h"
#include "../../Mesh/Mesh.h"
#include "../../Renderer/TextMaster.h"
#include "../../Mesh/VertexArray.h"

class Text::FontType;

namespace Text
{
	class GUIText {
	private:
		std::string m_TextString;
		float m_FontSize;

		int m_TextMeshVao;
		int m_VertexCount;
		glm::vec3 m_Colour = { 0.6f, 0.5f, 0.2f };

		glm::vec2 m_Position;
		float m_LineMaxSize;
		int m_NumberOfLines;

		FontType m_Font;

		bool m_CenterText = false;

		Mesh* m_Mesh;
		//VertexArray m_VAO;

	public:
		GUIText(const std::string& text, float fontSize, FontType& font, glm::vec2 position, float maxLineLength, bool centered);

		void Remove();

		FontType& GetFont();
		void SetColour(float r, float g, float b);
		glm::vec3& GetColour();
		int GetNumberOfLines();
		glm::vec2& GetPosition();

		void Bind();
		void Unbind();

		int GetMesh();
		void SetMesh(std::vector<float>& positions, std::vector<float>& coords);
		void SetMeshInfo(int vao, int verticesCount);
		int GetVertexCount();

		float GetFontSize();
		void SetNumberOfLines(int number);
		bool IsCentered();
		float GetMaxLineSize();
		const std::string& GetTextString();
	};
}