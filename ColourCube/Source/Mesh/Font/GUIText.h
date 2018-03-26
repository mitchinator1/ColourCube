#ifndef GUI_TEXT_H
#define GUI_TEXT_H
#include "GLM/glm.hpp"
#include <string>
#include <memory>

#include "FontType.h"
#include "../../Mesh/Mesh.h"
#include "../../Mesh/VertexArray.h"

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
		int m_NumberOfLines = 0;

		Mesh* m_Mesh;

		glm::vec3 m_Colour = { 1.0f, 1.0f, 0.8f };

	public:
		GUIText(const std::string& text, float fontSize, std::shared_ptr<FontType> font, glm::vec2 position, float maxLineLength, bool centered);

		void Remove();

		void Bind();
		void Unbind();
		
		void UpdateIndices();
		void SetColour(float r, float g, float b);
		void SetNumberOfLines(int number);

		glm::vec3& GetColour()						{ return m_Colour; }

		inline const std::string& GetTextString()	{ return m_TextString; }
		inline float GetFontSize()					{ return m_FontSize; }
		FontType& GetFont()							{ return *m_Font; }
		glm::vec2& GetPosition()					{ return m_Position; }
		inline float GetMaxLineSize()				{ return m_LineMaxSize; }
		inline bool IsCentered()					{ return m_CenterText; }
		inline int GetNumberOfLines()				{ return m_NumberOfLines; }
		inline unsigned int GetCount()				{ return m_Mesh->GetCount(); }
	};
}

#endif