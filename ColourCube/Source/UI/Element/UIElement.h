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

		friend class UIBuilder;

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
		UIElement* SetPosition(const glm::vec3& position);
		UIElement* SetTime(float time);

		virtual void Build();
		bool UpdateNeeded();
		void UpdateFinished();

		virtual bool IsMouseOver();
		virtual bool IsMouseDown();

		virtual std::string& GetID();
		std::vector<float> GetVertices();
		virtual UIElement* GetElement(const std::string& id);
		virtual std::vector<std::unique_ptr<UIElement>>& GetElements()	{ return m_Elements; }
		virtual std::shared_ptr<UIText>& GetText()						{ return m_Text; }
		virtual glm::vec4& GetColour()									{ return colour; }
		inline auto& GetPosition()										{ return m_Position; }
		inline bool IsHidden()		const								{ return m_Hidden; }

	protected:
		std::vector<float> CalculateVertices();
		void UpdateTextPosition();

	};
}

#endif