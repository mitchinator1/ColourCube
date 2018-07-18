#ifndef UI_BACKGROUND_H
#define UI_BACKGROUND_H
#include <vector>
#include <memory>
#include "GLM/glm.hpp"
#include "UIText.h"

namespace UI
{
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
		SHOW,
		HIDE,
		ADD_COLOUR,
		UNDO,
		REDO
	};

	class UIElement
	{
	public:
		float minX, minY, maxX, maxY;
		glm::vec4 colour;

	protected:
		glm::vec3 m_Position;
		std::string m_ID;
		float m_PersistantAlpha;
		float m_Depth;
		bool m_UpdateNeeded = false;
		bool m_Hidden = false;

		float m_Time = 0.0f;
		float m_TargetTime = 0.0f;

		bool m_IsMouseOver = false;
		ACTION m_MouseOver = ACTION::NONE;
		ACTION m_MouseOut = ACTION::NONE;

		bool m_IsMouseDown = false;
		ACTION m_MouseDown = ACTION::NONE;
		ACTION m_MouseUp = ACTION::NONE;

		std::vector<std::unique_ptr<UIElement>> m_Elements;
		std::shared_ptr<UIText> m_Text;

	public:
		UIElement() noexcept;
		virtual ~UIElement();

		virtual void Update();
		virtual bool InRange(float x, float y);
		virtual void Reveal(bool reveal = true);
		virtual void Reveal(const std::string& id);
		virtual void Hide(bool hide = true);

		virtual ACTION OnMouseOver();
		virtual ACTION OnMouseOut();
		virtual ACTION OnMouseDown();
		virtual ACTION OnMouseUp();

		virtual void AddElement(std::unique_ptr<UIElement>& element);
		virtual void AddText(std::shared_ptr<UIText>& text);

		UIElement* SetID(const std::string& id);
		UIElement* SetColour(float r, float g, float b);
		UIElement* SetPosition(const glm::vec3& position);
		UIElement* SetAlpha(float alpha);
		UIElement* SetPersistantAlpha(float alpha);
		UIElement* SetDepth(float depth);
		UIElement* SetTime(float time);
		UIElement* SetMouseOver(const std::string& action);
		UIElement* SetMouseOut(const std::string& action);
		UIElement* SetMouseDown(const std::string& action);
		UIElement* SetMouseUp(const std::string& action);

		virtual void Build();

		virtual UIElement* GetElement(const std::string& id);
		virtual std::vector<std::unique_ptr<UIElement>>& GetElements()	{ return m_Elements; }
		virtual std::shared_ptr<UIText>& GetText()						{ return m_Text; }

		virtual glm::vec4& GetColour()			{ return colour; }
		virtual bool IsMouseOver();
		virtual bool IsMouseDown()				{ return m_IsMouseDown; }

		std::vector<float> GetVertices();

		virtual std::string& GetID()			{ return m_ID; }
		inline auto& GetPosition()				{ return m_Position; }
		inline bool IsHidden()			const	{ return m_Hidden; }
		bool UpdateNeeded();
		void UpdateFinished();

	protected:
		std::vector<float> CalculateVertices();
		void UpdateTextPosition();

	private:
		ACTION StringToEnum(const std::string& value);

	};
}

#endif