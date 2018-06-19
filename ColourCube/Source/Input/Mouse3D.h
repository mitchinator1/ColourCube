#ifndef MOUSE_3D_H
#define MOUSE_3D_H
#include "MouseBase.h"
#include "GLM/glm.hpp"

namespace Camera { class CameraBase; }
class Level;

namespace Input
{
	class Mouse3D : public MouseBase
	{
	protected:
		glm::vec3 m_CurrentPoint	= { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_CurrentRay		= { 0.0f, 0.0f, 0.0f };

		std::shared_ptr<Camera::CameraBase> m_Camera;

	public:
		Mouse3D(std::shared_ptr<Display>& display);
		virtual ~Mouse3D();

		virtual void HandleEvents()			= 0;
		virtual void Update(Level& level)	= 0;
		virtual bool ToggleMode()			= 0;

		inline auto& GetCurrentPoint()		{ return m_CurrentPoint; }
		inline auto& GetCurrentRay()		{ return m_CurrentRay; }

	protected:
		glm::vec3 CalculateMouseRay();
		
	private:
		glm::vec2 GetNormalizedDeviceCoords();
		glm::vec4 ToEyeCoords(glm::vec4 clipCoords);
		glm::vec3 ToWorldCoords(glm::vec4 eyeCoords);

	};
}

#endif