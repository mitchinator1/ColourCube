#ifndef UI_SCROLLBOX_H
#define UI_SCROLLBOX_H
#include "UIElement.h"

namespace UI
{
	class UISlider;
	class UIButton;
	class UIDragBar;
	class UITextEntry;

	class UIScrollbox : public UIElement
	{
	private:
		float m_Spacing = 3.0f;
		float m_PrevX = 0.0f;

	public:
		UIScrollbox();
		~UIScrollbox();
		
		void AddElement(std::shared_ptr<UIElement>& element)	override;
		void AddElement(std::shared_ptr<UISlider>& element);
		void AddElement(std::shared_ptr<UIButton>& element);
		void AddElement(std::shared_ptr<UIDragBar>& element);
		void AddElement(std::shared_ptr<UITextEntry>& element);

		void Deactivate();
		bool IsActive() const;

	protected:
		void AddTraits()										override;
	};
}

#endif