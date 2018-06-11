#include "EditorMousePicker.h"
#include "../Camera/CameraBase.h"

namespace Input
{
	EditorMousePicker::EditorMousePicker(std::shared_ptr<Camera::CameraBase>& camera, std::shared_ptr<Display>& display)
		:MouseBase(display)
	{
		MouseBase::m_Camera = camera;
	}

	void EditorMousePicker::HandleEvents()
	{
		GetMouseInput();
	}

	void EditorMousePicker::Update(Level& level)
	{
		if (m_Toggled)
		{
			m_CurrentRay = CalculateMouseRay();

			CubeIntersection(m_CurrentRay, level);
		}
	}

	bool EditorMousePicker::ToggleMode()
	{
		m_AddCubeToggled = !m_AddCubeToggled;
		return m_AddCubeToggled;
	}

	void EditorMousePicker::CubeIntersection(glm::vec3 ray, Level& level)
	{
		glm::vec3 start = m_Camera->GetPosition();
		glm::vec3 curRay;

		std::vector<glm::vec3> targets = {
		{ -2.0f,	-1.0f,	-2.0f },
		{ -1.0f,	-1.0f,	-2.0f },
		{ 0.0f,		-1.0f,	-2.0f },
		{ 1.0f,		-1.0f,	-2.0f },
		{ 2.0f,		-1.0f,	-2.0f },
		{ -2.0f,	-1.0f,	-1.0f },
		{ -1.0f,	-1.0f,	-1.0f },
		{ 0.0f,		-1.0f,	-1.0f },
		{ 1.0f,		-1.0f,	-1.0f },
		{ 2.0f,		-1.0f,	-1.0f },
		{ -2.0f,	-1.0f,	0.0f },
		{ -1.0f,	-1.0f,	0.0f },
		{ 0.0f,		-1.0f,	0.0f },
		{ 1.0f,		-1.0f,	0.0f },
		{ 2.0f,		-1.0f,	0.0f },
		{ -2.0f,	-1.0f,	1.0f },
		{ -1.0f,	-1.0f,	1.0f },
		{ 0.0f,		-1.0f,	1.0f },
		{ 1.0f,		-1.0f,	1.0f },
		{ 2.0f,		-1.0f,	1.0f },
		{ -2.0f,	-1.0f,	2.0f },
		{ -1.0f,	-1.0f,	2.0f },
		{ 0.0f,		-1.0f,	2.0f },
		{ 1.0f,		-1.0f,	2.0f },
		{ 2.0f,		-1.0f,	2.0f },
		};

		for (auto& cube : level.GetCubes())
		{
			targets.emplace_back(cube.GetPosition());
		}

		for (unsigned int i = 0; i < m_RecursiveCount; ++i)
		{
			curRay = start + (ray * (i / 30.0f));
			for (auto& target : targets)
			{
				if (curRay.x >= target.x - 0.5f && curRay.x <= target.x + 0.5f &&
					curRay.z >= target.z - 0.5f && curRay.z <= target.z + 0.5f &&
					curRay.y >= target.y - 0.5f && curRay.y <= target.y + 0.5f)
				{

					if (m_AddCubeToggled)
					{
						glm::vec3 newRay = (curRay + (start + (ray * ((i - 1) / 30.0f)))) / 2.0f;
						AddCube(newRay, target, level);
					}
					else
					{
						level.RemoveCube(target.x, target.y, target.z);
					}
					
					return;
				}
			}
		}
	}

	void EditorMousePicker::AddCube(glm::vec3 hitPoint, glm::vec3 target, Level& level)
	{
		const float epsilon = 0.015f;

		if (abs(hitPoint.z - target.z - 0.5f) < epsilon)
		{
			level.AddCube(target.x, target.y, target.z + 1);
		}
		else if (abs(hitPoint.z - target.z + 0.5f) < epsilon)
		{
			level.AddCube(target.x, target.y, target.z - 1);
		}
		else if (abs(hitPoint.x - target.x + 0.5f) < epsilon)
		{
			level.AddCube(target.x - 1, target.y, target.z);
		}
		else if (abs(hitPoint.x - target.x - 0.5f) < epsilon)
		{
			level.AddCube(target.x + 1, target.y, target.z);
		}
		else if (abs(hitPoint.y - target.y - 0.5f) < epsilon)
		{
			level.AddCube(target.x, target.y + 1, target.z);
		}
		else if (abs(hitPoint.y - target.y + 0.5f) < epsilon)
		{
			level.AddCube(target.x, target.y - 1, target.z);
		}
	}

}