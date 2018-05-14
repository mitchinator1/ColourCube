#ifndef UI_BACKGROUND_H
#define UI_BACKGROUND_H
#include <vector>
#include <memory>
#include "GLM/glm.hpp"

class Mesh;

namespace UI
{
	enum class TYPE
	{
		BACKGROUND,
		TEXTBOX,
		BUTTON,
		SLIDER,
		COLOUR_CHOOSER
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
		COLOUR
	};

	class UIElement
	{
	private:
		glm::vec3 m_Colour;
		glm::vec3 m_Position;
		float m_Alpha;
		float m_Depth;
		float m_Width;
		bool m_Hidden = false;
		ACTION m_Action;

		float m_Value;

		std::unique_ptr<Mesh> m_Mesh;

	public:
		UIElement();
		UIElement(float x, float y, float xSize, float ySize);
		~UIElement();

		void Bind();
		void Unbind();

		void OnMouseOver();
		void OnMouseOut();
		ACTION OnMouseDown();

		UIElement* SetMin(float x, float y);
		UIElement* SetMax(float x, float y);
		UIElement* SetColour(float r, float g, float b);
		UIElement* SetPosition(glm::vec3 position);
		UIElement* SetAlpha(float alpha);
		UIElement* SetDepth(float depth);
		UIElement* SetValue(float value);
		UIElement* SetWidth(float width);
		UIElement* SetHidden(bool hide);
		UIElement* SetAction(ACTION action);
		UIElement* SetAction(const std::string& action);

		void Build();

		unsigned int GetCount();

		inline auto GetAlpha()		{ return m_Alpha; }
		inline auto GetPosition()	{ return m_Position; }
		inline auto GetValue()		{ return m_Value; }
		inline auto GetWidth()		{ return m_Width; }
		inline auto IsHidden()		{ return m_Hidden; }

	private:
		std::vector<float> CalculateVertices();
		ACTION StringToEnum(const std::string& value);

	public:
		float minX, minY, maxX, maxY;

	};
}

#endif