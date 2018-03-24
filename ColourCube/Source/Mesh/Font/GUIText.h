#pragma once
#include "GLM/glm.hpp"
#include <string>
#include <memory>

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
		std::shared_ptr<FontType> m_Font;
		glm::vec2 m_Position;
		float m_LineMaxSize;
		bool m_CenterText = false;

		int m_NumberOfLines;
		unsigned int m_VertexCount;

		Mesh* m_Mesh;

		glm::vec3 m_Colour = { 1.0f, 1.0f, 0.8f };

	public:
		GUIText(const std::string& text, float fontSize, std::shared_ptr<FontType> font, glm::vec2 position, float maxLineLength, bool centered);

		void Remove();

		FontType& GetFont();
		void SetColour(float r, float g, float b);
		glm::vec3& GetColour();
		int GetNumberOfLines();
		glm::vec2& GetPosition();

		void Bind();
		void Unbind();
 
		unsigned int GetCount();

		float GetFontSize();
		void SetNumberOfLines(int number);
		bool IsCentered();
		float GetMaxLineSize();
		const std::string& GetTextString();
	};
}