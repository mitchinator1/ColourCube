#pragma once
#include "GLM/glm.hpp"
#include <string>

#include "FontType.h"
#include "../../Renderer/TextMaster.h"

namespace Text
{
	class GUIText {
	private:
		std::string m_TextString;
		float m_FontSize;

		int m_TextMeshVao;
		int m_VertexCount;
		glm::vec3 m_Colour = { 0.0f, 0.0f, 0.0f };

		glm::vec2 m_Position;
		float m_LineMaxSize;
		int m_NumberOfLines;

		FontType m_Font;

		bool m_CenterText = false;

	public:
		GUIText(const std::string& text, float fontSize, FontType font, glm::vec2 position, float maxLineLength, bool centered);

		void Remove();

		FontType& GetFont();
		void SetColour(float r, float g, float b);
		glm::vec3& GetColour();
		int GetNumberOfLines();
		glm::vec2& GetPosition();

		int GetMesh();
		void SetMeshInfo(int vao, int verticesCount);
		int GetVertexCount();

		float GetFontSize();
		void SetNumberOfLines(int number);
		bool IsCentered();
		float GetMaxLineSize();
		const std::string& GetTextString();
	};
}