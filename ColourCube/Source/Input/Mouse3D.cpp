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

	glm::vec3 Mouse3D::CalculateMouseRay()
	{
		glm::vec2 normCoords = GetNormalizedDeviceCoords();
		glm::vec4 clipCoords = { normCoords.x, normCoords.y, -1.0f, 1.0f };
		glm::vec4 eyeCoords = ToEyeCoords(clipCoords);
		glm::vec3 worldRay = ToWorldCoords(eyeCoords);

		return worldRay;
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