#ifndef MOUSE_BASE_H
#define MOUSE_BASE_H
#include <memory>
#include "MouseBase.h"
#include "../Display.h"

namespace Input
{
	class MouseBase
	{
	protected:
		bool m_Toggled		= false;
		bool m_Held			= false;
		float m_ToggledTime = 0.0f;
		const float DELAY	= 0.25f;

		double mouseX		= 0.0f;
		double mouseY		= 0.0f;

		std::shared_ptr<Display> m_Display;

	public:
		MouseBase(std::shared_ptr<Display>& display);
		virtual ~MouseBase() {};

		inline bool IsToggled() const { return m_Toggled; }
		inline bool IsHeld()	const { return m_Held; }
		
	protected:
		void GetMouseInput();

	};
}

#endif
