#include "Mouse3D.h"
#include "../Camera/CameraBase.h"

namespace Input
{
	Mouse3D::Mouse3D(std::shared_ptr<Display>& display)
		: MouseBase(display), m_Camera(nullptr)
	{

	}

	Mouse3D::~Mouse3D()
	{

	}

	void Mouse3D::CalculateMouseRay()
	{
		glm::vec2 normCoords = GetNormalizedDeviceCoords();
		glm::vec4 clipCoords = { normCoords.x, normCoords.y, -1.0f, 1.0f };
		glm::vec4 eyeCoords = ToEyeCoords(clipCoords);
		glm::vec3 worldRay = ToWorldCoords(eyeCoords);

		m_CurrentRay = worldRay;
	}

	bool Mouse3D::MouseRayIntersects(Level& level)
	{
		auto& camera = m_Camera->GetPosition();
		float size = 0.5f;

		for (unsigned int i = 0; i < RECURSIVE_COUNT; ++i)
		{
			auto ray = camera + (m_CurrentRay * (i / 30.0f));
			for (auto& target : m_Targets)
			{
				if (ray.x >= target.x - size && ray.x <= target.x + size &&
					ray.z >= target.z - size && ray.z <= target.z + size &&
					ray.y >= target.y - size && ray.y <= target.y + size)
				{
					m_CurrentTarget = target;
					m_CurrentRay = (ray + (camera + (m_CurrentRay * ((i - 1) / 30.0f)))) / 2.0f;
					return true;
				}
			}
		}
		return false;
	}

	glm::vec2 Mouse3D::GetNormalizedDeviceCoords()
	{
		float x = (2.0f * (float)mouseX) / m_Display->Width - 1.0f;
		float y = 1.0f - (2.0f * (float)mouseY) / m_Display->Height;

		return glm::vec2(x, y);
	}

	glm::vec4 Mouse3D::ToEyeCoords(glm::vec4 clipCoords)
	{
		glm::vec4 eyeCoords = glm::inverse(m_Camera->GetProjectionMatrix()) * clipCoords;

		return glm::vec4(eyeCoords.x, eyeCoords.y, -1.0f, 0.0f);
	}

	glm::vec3 Mouse3D::ToWorldCoords(glm::vec4 eyeCoords)
	{
		glm::vec4 rayWorld = glm::inverse(m_Camera->GetViewMatrix()) * eyeCoords;
		glm::vec3 mouseRay = { rayWorld.x, rayWorld.y, rayWorld.z };

		return glm::normalize(mouseRay);
	}
}