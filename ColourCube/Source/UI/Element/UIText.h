#ifndef UI_TEXT_H
#define UI_TEXT_H
#include <string>
#include <memory>
#include "GLM/glm.hpp"
#include "../../Mesh/Mesh.h"

namespace Text { class FontType; }

namespace UI
{
	class UIText {
	private:
		float m_FontSize;
		glm::vec2 m_Position;
		float m_LineMaxSize;
		bool m_CenterText;

		int m_NumberOfLines = 0;

		glm::vec3 m_Colour{ 1.0f, 1.0f, 1.0f };
		std::string m_TextString;
		//TODO: Add alignment

	protected:
		std::string m_Font;
		std::string m_KeyString = "default";
		unsigned int m_KeyNumber = 0;
		std::unique_ptr<Mesh> m_Mesh;
		bool m_UpdateNeeded;
		bool m_Created;
		bool m_Added = false;
		bool m_RemovalNeeded = false;
		bool m_Hidden = false;
		unsigned int m_TotalChar;

		float m_Time = 0.0f;
		float m_PrevTime = 0.0f;
		float m_TargetTime = 0.0f;

	public:
		UIText() noexcept;
		~UIText();

		void CreateMesh(const Text::FontType* font);

		void Bind()		const;
		void Unbind()	const;

		virtual void Update();
		virtual bool Continue();
		void Reveal();
		void Hide();

		void Added();
		void Remove();

		void SetNumberOfLines(int number);
		UIText* SetPosition(float x, float y);
		UIText* SetSize(float size);
		UIText* SetLineSize(float size);
		UIText* SetColour(float r, float g, float b);
		UIText* SetFont(const std::string& font);
		UIText* SetKey(const std::string& key);
		UIText* SetKeyNumber(unsigned int number);
		UIText* SetTime(float time);
		UIText* SetCenter(bool centered = true);

		inline auto GetKeyNumber()			const	{ return m_KeyNumber; }
		inline const auto& GetTextString()	const	{ return m_TextString; }
		inline auto GetFont()						{ return m_Font; }
		inline float GetFontSize()			const	{ return m_FontSize; }
		inline glm::vec2& GetPosition()				{ return m_Position; }
		inline float GetMaxLineSize()		const	{ return m_LineMaxSize; }
		inline bool IsCentered()			const	{ return m_CenterText; }
		inline bool isCreated()				const	{ return m_Created; }
		inline bool UpdateNeeded()			const	{ return m_UpdateNeeded; }
		inline bool IsAdded()				const	{ return m_Added; }
		inline bool RemovalNeeded()			const	{ return m_RemovalNeeded; }
		inline bool IsHidden()				const	{ return m_Hidden; }
		inline int GetNumberOfLines()		const	{ return m_NumberOfLines; }
		inline glm::vec3& GetColour()				{ return m_Colour; }
		inline unsigned int GetCount()		const	{ return m_Mesh->GetCount(); }

	protected:
		void LoadText();

		inline const auto GetKey()					{ return m_KeyString + std::to_string(m_KeyNumber); }
	};
}

#endif