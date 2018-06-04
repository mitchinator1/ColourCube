#ifndef UI_BACKGROUND_H
#define UI_BACKGROUND_H
#include <vector>
#include <memory>
#include <iostream>
#include "GLM/glm.hpp"
#include "UIText.h"

class Mesh;

namespace UI
{
	enum class TYPE
	{
		BACKGROUND,
		TEXTBOX,
		BUTTON,
		SLIDER,
		POPUP
	};

	enum class ACTION
	{
		NONE,
		PLAY,
		EDITOR,
		SETTINGS,
		EXIT,
		MENU,
		CONTINUE,
		LOAD,
		SAVE,
		TOGGLE,
		SHOW_MENU,
		SHOW_EDIT,
		SHOW_COLOUR,
		HIDE_MENU,
		HIDE_EDIT,
		HIDE_COLOUR,
		ADD_COLOUR
	};

	class UIText;

	class UIElement
	{
	public:
		float minX, minY, maxX, maxY;
		glm::vec3 colour;

	private:
		glm::vec3 m_Position;

	protected:
		std::unique_ptr<Mesh> m_Mesh;
		float m_Alpha;
		float m_PersistantAlpha;
		float m_Depth;
		bool m_Hidden = false;

		ACTION m_MouseOver = ACTION::NONE;
		bool m_IsMouseOver = false;
		ACTION m_MouseOut = ACTION::NONE;
		ACTION m_MouseDown = ACTION::NONE;

		std::vector<std::unique_ptr<UIElement>> m_Elements;
		std::shared_ptr<UIText> m_Text;

	public:
		UIElement() noexcept;
		virtual ~UIElement();

		void Bind();
		void Unbind();

		virtual void Update();
		virtual bool InRange(float x, float y);
		virtual void Reveal(bool reveal = true);
		virtual void Hide(bool hide = true);

		virtual ACTION OnMouseOver();
		virtual ACTION OnMouseOut();
		virtual ACTION OnMouseDown();

		virtual void AddElement(std::unique_ptr<UIElement>& element);
		virtual void AddText(std::shared_ptr<UIText>& text);

		void BindValue(float* c);

		UIElement* SetColour(float r, float g, float b);
		UIElement* SetPosition(const glm::vec3& position);
		UIElement* SetAlpha(float alpha);
		UIElement* SetPersistantAlpha(float alpha);
		UIElement* SetDepth(float depth);
		UIElement* SetMouseOver(ACTION action);
		UIElement* SetMouseOver(const std::string& action);
		UIElement* SetMouseOut(ACTION action);
		UIElement* SetMouseOut(const std::string& action);
		UIElement* SetMouseDown(ACTION action);
		UIElement* SetMouseDown(const std::string& action);

		virtual void Build();

		virtual std::vector<std::unique_ptr<UIElement>>& GetElements() { return m_Elements; }
		virtual std::shared_ptr<UIText>& GetText() { return m_Text; }

		unsigned int GetCount();

		//GetColour
		inline auto GetAlpha()		{ return m_Alpha; }
		inline auto GetPosition()	{ return m_Position; }
		inline bool IsHidden()		{ return m_Hidden; }
		inline bool IsMouseOver()	{ return m_IsMouseOver; }

	protected:
		std::vector<float> CalculateVertices();

	private:
		ACTION StringToEnum(const std::string& value);

	};
}

#endif