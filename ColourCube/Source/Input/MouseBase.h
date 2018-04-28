#ifndef MOUSE_BASE_H
#define MOUSE_BASE_H
#include "GLM/glm.hpp"
#include "../Level/Level.h"

namespace Input
{
	class MouseBase
	{
	protected:
		glm::vec3 m_CurrentPoint = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_CurrentRay = { 0.0f, 0.0f, 0.0f };

		bool MouseButtonIsPressed = false;
		float Toggled = 0.0f;

		double mouseX = 0.0f;
		double mouseY = 0.0f;

	public:
		MouseBase() {};
		~MouseBase() {};

		virtual void HandleEvents() = 0;
		virtual void Update(Level& level) = 0;
		virtual void ToggleMode() = 0;

		inline glm::vec3& GetCurrentPoint() { return m_CurrentPoint; }
		inline glm::vec3& GetCurrentRay() { return m_CurrentRay; }
	};
}

#endif
