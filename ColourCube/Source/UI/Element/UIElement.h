#ifndef UI_ELEMENT_H
#define UI_ELEMENT_H
#include <vector>
#include <memory>
#include "../../Entity/EntityBase.h"
#include "UIText.h"

namespace UI
{
	//TODO: Event system?
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
		REDO,
		NEXT_STEP,
		PREV_STEP
	};

	class UIElement : public Entity::EntityBase
	{
	public:
		float width, height;

	protected:
		std::string m_ID;
		float m_PersistantAlpha;

		bool m_TraitsAdded	= false;
		bool m_IsBuilt		= false;
		bool m_UpdateNeeded = false;
		bool m_Hidden		= false;
		bool m_Active		= false;
		float m_Time = 0.0f;
		float m_TargetTime = 0.0f;

		//TODO: State system
		bool m_IsMouseOver = false;
		ACTION m_MouseOver = ACTION::NONE;
		ACTION m_MouseOut = ACTION::NONE;
		bool m_IsMouseDown = false;
		ACTION m_MouseDown = ACTION::NONE;
		ACTION m_MouseUp = ACTION::NONE;

		std::vector<std::shared_ptr<UIElement>> m_Elements;
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

		virtual void AddElement(std::shared_ptr<UIElement>& element);
		virtual void AddText(std::shared_ptr<UIText>& text);

		UIElement* SetID(const std::string& id);
		UIElement* SetPosition(const glm::vec3& position);
		UIElement* SetTime(float time);

		virtual void Build();
		bool UpdateNeeded();
		void UpdateFinished();

		virtual void Activate()		{ m_Active = true; }
		virtual void Deactivate()	{ m_Active = false; }

		virtual bool IsMouseOver();
		virtual bool IsMouseDown();

		virtual std::string& GetID();
		virtual std::string& GetParentID();
		std::vector<float> GetVertices();
		virtual UIElement* GetElement(const std::string& id);
		virtual std::vector<std::shared_ptr<UIElement>>& GetElements()	{ return m_Elements; }
		virtual std::shared_ptr<UIText>& GetText()						{ return m_Text; }
		virtual glm::vec4& GetColour()									{ return colour; }

		inline bool IsBuilt()		const								{ return m_IsBuilt; }
		inline bool IsHidden()		const								{ return m_Hidden; }
		virtual bool IsActive()		const								{ return m_Active; }
		virtual UIElement* GetActiveElement();

	protected:
		std::vector<float> CalculateVertices();
		void UpdateTextPosition();

		virtual void AddTraits() { }

	};
}

#endif