#ifndef UI_TEXT_H
#define UI_TEXT_H
#include <string>
#include <memory>
#include <vector>
#include "GLM/glm.hpp"

namespace Text { class FontType; }

namespace UI
{
	class UIText {
	public:
		//TODO: Standardize X, Y, and m_Position
		//TODO: Make entity
		float X = 0.0f, Y = 0.0f;

	private:
		float m_FontSize;
		glm::vec3 m_Position;
		float m_LineMaxSize;
		bool m_CenterText;

		glm::vec3 m_Colour{ 1.0f, 1.0f, 1.0f };
		std::vector<float> m_Vertices;

		std::string m_TextString = "";
		//TODO: Add alignment

	protected:
		std::string m_Font;
		std::string m_KeyString = "";
		unsigned int m_KeyNumber = 0;
		bool m_UpdateNeeded = false;
		bool m_Created			= false;
		bool m_Added			= false;
		bool m_RemovalNeeded	= false;
		bool m_Hidden			= false;
		unsigned int m_TotalChar;

		float m_Time = 0.0f;
		float m_PrevTime = 0.0f;
		float m_TargetTime = 0.0f;

	public:
		UIText() noexcept;
		~UIText();

		void CreateMesh(std::shared_ptr<Text::FontType> font);
		
		virtual void Update();
		virtual bool Continue();
		void Reveal();
		void Hide();

		void Added();
		void Remove();

		UIText* SetPosition(float x, float y);
		UIText* SetSize(float size);
		UIText* SetLineSize(float size);
		UIText* SetColour(float r, float g, float b);
		UIText* SetFont(const std::string& font);
		UIText* SetKey(const std::string& key);
		UIText* SetKeyNumber(unsigned int number);
		UIText* AddLetter(const std::string& letter);
		UIText* SetTime(float time);
		UIText* SetCenter(bool centered = true);

		inline auto GetVertices()					{ return m_Vertices; }
		inline auto GetKeyNumber()			const	{ return m_KeyNumber; }
		inline auto& GetTextString()				{ return m_TextString; }
		inline auto GetFont()						{ return m_Font; }
		inline float GetFontSize()			const	{ return m_FontSize; }
		inline auto& GetPosition()					{ return m_Position; }
		inline float GetMaxLineSize()		const	{ return m_LineMaxSize; }
		inline bool IsCentered()			const	{ return m_CenterText; }
		inline bool isCreated()				const	{ return m_Created; }
		inline bool UpdateNeeded()			const	{ return m_UpdateNeeded; }
		inline bool IsAdded()				const	{ return m_Added; }
		inline bool RemovalNeeded()			const	{ return m_RemovalNeeded; }
		inline bool IsHidden()				const	{ return m_Hidden; }
		inline auto& GetColour()					{ return m_Colour; }

	protected:
		void LoadText();

		inline const auto GetKey()					{ return m_KeyString + std::to_string(m_KeyNumber); }
	};
}

#endif