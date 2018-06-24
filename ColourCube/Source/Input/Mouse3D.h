#ifndef MOUSE_3D_H
#define MOUSE_3D_H
#include <vector>
#include "MouseBase.h"
#include "GLM/glm.hpp"

namespace Camera { class CameraBase; }
class Level;
class Cube;

namespace Input
{
	class Mouse3D : public MouseBase
	{
	private:
		const unsigned int RECURSIVE_COUNT = 400;

	protected:
		glm::vec3 m_CurrentTarget	= { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_CurrentRay		= { 0.0f, 0.0f, 0.0f };
		std::vector<glm::vec3> m_Targets;

		std::shared_ptr<Camera::CameraBase> m_Camera;

	public:
		Mouse3D(std::shared_ptr<Display>& display);
		virtual ~Mouse3D();

		virtual void HandleEvents()													= 0;
		virtual void Update(Level& level)											= 0;
		virtual bool ToggleMode()													= 0;
		virtual void CalculateTargets(std::vector<std::unique_ptr<Cube>>& cubes)	= 0;

		inline auto& GetCurrentTarget()		{ return m_CurrentTarget; }
		inline auto& GetCurrentRay()		{ return m_CurrentRay; }

	protected:
		void CalculateMouseRay();
		bool MouseRayIntersects(Level& level);
		
	private:
		glm::vec2 GetNormalizedDeviceCoords();
		glm::vec4 ToEyeCoords(glm::vec4 clipCoords);
		glm::vec3 ToWorldCoords(glm::vec4 eyeCoords);

	};
}

#endif