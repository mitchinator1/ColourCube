#ifndef MOUSE_BASE_H
#define MOUSE_BASE_H
#include "GLM/glm.hpp"
#include "../Level/Level.h"

namespace Input
{
	class MouseBase
	{
	protected:
		glm::vec3 m_CurrentPoint	= { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_CurrentRay		= { 0.0f, 0.0f, 0.0f };

		bool m_MouseButtonIsPressed = false;
		float m_ToggledTime = 0.0f;
		const float DELAY = 0.2f;

		double mouseX = 0.0f;
		double mouseY = 0.0f;

	public:
		MouseBase() noexcept {};
		~MouseBase() {};

		virtual void HandleEvents() = 0;
		virtual void Update(Level& level) = 0;
		virtual bool ToggleMode() = 0;

		inline auto& GetCurrentPoint()	{ return m_CurrentPoint; }
		inline auto& GetCurrentRay()	{ return m_CurrentRay; }
	};
}

#endif
