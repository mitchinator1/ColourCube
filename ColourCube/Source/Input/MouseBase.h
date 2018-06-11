#ifndef MOUSE_BASE_H
#define MOUSE_BASE_H
#include <memory>
#include "GLM/glm.hpp"
#include "../Level/Level.h"
#include "../Display.h"

namespace Camera { class CameraBase; }

namespace Input
{
	class MouseBase
	{
	protected:
		glm::vec3 m_CurrentPoint	= { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_CurrentRay		= { 0.0f, 0.0f, 0.0f };

		bool m_Toggled = false;
		bool m_Held = false;
		float m_ToggledTime = 0.0f;
		const float DELAY = 0.2f;

		double mouseX = 0.0f;
		double mouseY = 0.0f;

		std::shared_ptr<Display> m_Display;
		std::shared_ptr<Camera::CameraBase> m_Camera;

	public:
		MouseBase(std::shared_ptr<Display>& display);
		virtual ~MouseBase() {};

		virtual void HandleEvents()			= 0;
		virtual void Update(Level& level)	= 0;
		virtual bool ToggleMode()			= 0;

	protected:
		void GetMouseInput();

		glm::vec3 CalculateMouseRay();
		glm::vec2 GetNormalizedDeviceCoords();
		glm::vec4 ToEyeCoords(glm::vec4 clipCoords);
		glm::vec3 ToWorldCoords(glm::vec4 eyeCoords);

	public:
		inline auto& GetCurrentPoint()	{ return m_CurrentPoint; }
		inline auto& GetCurrentRay()	{ return m_CurrentRay; }

	};
}

#endif
