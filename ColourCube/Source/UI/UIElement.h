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
		HITBOX
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
		TOGGLE
	};

	class UIElement
	{
	private:
		glm::vec3 m_Colour;
		glm::vec3 m_Position;
		float m_Alpha;
		float m_Depth;
		float m_Value;
		ACTION m_Action;

		std::unique_ptr<Mesh> m_Mesh;

	public:
		UIElement(float x, float y, float xSize, float ySize);
		~UIElement();

		void Bind();
		void Unbind();

		UIElement* SetColour(float r, float g, float b);
		UIElement* SetPosition(glm::vec3 position);
		UIElement* SetAlpha(float alpha);
		UIElement* SetDepth(float depth);
		UIElement* SetValue(float value);
		UIElement* SetAction(ACTION action);

		void Build();

		unsigned int GetCount();

		inline auto GetAlpha()		{ return m_Alpha; }
		inline auto GetPosition()	{ return m_Position; }
		inline auto GetValue()		{ return m_Value; }
		inline auto GetAction()		{ return m_Action; }

	private:
		std::vector<float> CalculateVertices();

	public:
		float minX, minY, maxX, maxY;

	};
}

#endif