#ifndef GUI_TEXT_H
#define GUI_TEXT_H
#include "GLM/glm.hpp"
#include <string>
#include <memory>
#include "../Mesh/Mesh.h"

namespace Text { class FontType; }

namespace UI
{
	class UIText {
	private:
		std::string m_TextString;
		float m_FontSize;
		glm::vec2 m_Position;
		float m_LineMaxSize;
		bool m_CenterText;
		int m_NumberOfLines = 0;

		std::unique_ptr<Mesh> m_Mesh;

		glm::vec3 m_Colour{ 0.3f, 0.5f, 1.0f };

	public:
		UIText(const std::string& text, float fontSize,	float x, float y, float maxLineLength = 100.0f, bool centered = true);
		~UIText();

		void CreateMesh(const Text::FontType* font);

		void Bind() const;
		void Unbind() const;
		
		void UpdateIndices();
		void SetNumberOfLines(int number);
		void SetColour(float r, float g, float b);

		inline const std::string& GetTextString()	const	{ return m_TextString; }
		inline float GetFontSize()					const	{ return m_FontSize; }
		inline glm::vec2& GetPosition()						{ return m_Position; }
		inline float GetMaxLineSize()				const	{ return m_LineMaxSize; }
		inline bool IsCentered()					const	{ return m_CenterText; }
		inline int GetNumberOfLines()				const	{ return m_NumberOfLines; }
		inline glm::vec3& GetColour()						{ return m_Colour; }
		inline unsigned int GetCount()				const	{ return m_Mesh->GetCount(); }
	};
}

#endif