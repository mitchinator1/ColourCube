#include "EditorMousePicker.h"
#include "../Camera/CameraBase.h"
#include "../Level/Level.h"

namespace Input
{
	EditorMousePicker::EditorMousePicker(std::shared_ptr<Camera::CameraBase>& camera, std::shared_ptr<Display>& display)
		:Mouse3D(display)
	{
		Mouse3D::m_Camera = camera;
		m_ShowSelection = true;
	}

	void EditorMousePicker::HandleEvents()
	{
		MouseBase::GetMouseInput();
	}

	void EditorMousePicker::Update(Level& level)
	{
		if (m_Toggled)
		{
			CalculateMouseRay();

			if (MouseRayIntersects(level))
				CubeIntersection(level);
		}
		if (m_ShowSelection)
		{
	
		}
	}

	bool EditorMousePicker::ToggleMode()
	{
		m_AddCubeToggled = !m_AddCubeToggled;
		return m_AddCubeToggled;
	}

	void EditorMousePicker::CalculateTargets(std::vector<std::unique_ptr<Cube>>& cubes)
	{
		m_Targets.clear();
		m_Targets.insert(m_Targets.end(), {
			{ -2.0f,	-1.0f,	-2.0f },
			{ -1.0f,	-1.0f,	-2.0f },
			{  0.0f,	-1.0f,	-2.0f },
			{  1.0f,	-1.0f,	-2.0f },
			{  2.0f,	-1.0f,	-2.0f },
			{ -2.0f,	-1.0f,	-1.0f },
			{ -1.0f,	-1.0f,	-1.0f },
			{  0.0f,	-1.0f,	-1.0f },
			{  1.0f,	-1.0f,	-1.0f },
			{  2.0f,	-1.0f,	-1.0f },
			{ -2.0f,	-1.0f,	 0.0f },
			{ -1.0f,	-1.0f,	 0.0f },
			{  0.0f,	-1.0f,	 0.0f },
			{  1.0f,	-1.0f,	 0.0f },
			{  2.0f,	-1.0f,	 0.0f },
			{ -2.0f,	-1.0f,	 1.0f },
			{ -1.0f,	-1.0f,	 1.0f },
			{  0.0f,	-1.0f,	 1.0f },
			{  1.0f,	-1.0f,	 1.0f },
			{  2.0f,	-1.0f,	 1.0f },
			{ -2.0f,	-1.0f,	 2.0f },
			{ -1.0f,	-1.0f,	 2.0f },
			{  0.0f,	-1.0f,	 2.0f },
			{  1.0f,	-1.0f,	 2.0f },
			{  2.0f,	-1.0f,	 2.0f },
		});

		for (auto& cube : cubes)
		{
			m_Targets.emplace_back(cube->GetPosition());
		}
	}

	void EditorMousePicker::CubeIntersection(Level& level)
	{
		if (m_AddCubeToggled)
		{
			AddCube(level);
		}
		else
		{
			level.RemoveCube(m_CurrentTarget.x, m_CurrentTarget.y, m_CurrentTarget.z);
		}
	}

	void EditorMousePicker::AddCube(Level& level)
	{
		const float epsilon = 0.015f;
		const float size	= 0.5f;
		const auto& camera	= m_Camera->GetPosition();

		if (camera.x > m_CurrentTarget.x && abs(m_CurrentRay.x - m_CurrentTarget.x - size) < epsilon)
		{
			level.AddCube(m_CurrentTarget.x + 1, m_CurrentTarget.y, m_CurrentTarget.z);
		}
		if (camera.x < m_CurrentTarget.x && abs(m_CurrentRay.x - m_CurrentTarget.x + size) < epsilon)
		{
			level.AddCube(m_CurrentTarget.x - 1, m_CurrentTarget.y, m_CurrentTarget.z);
		}
		if (camera.y > m_CurrentTarget.y && abs(m_CurrentRay.y - m_CurrentTarget.y - size) < epsilon)
		{
			level.AddCube(m_CurrentTarget.x, m_CurrentTarget.y + 1, m_CurrentTarget.z);
		}
		if (camera.y < m_CurrentTarget.y && abs(m_CurrentRay.y - m_CurrentTarget.y + size) < epsilon)
		{
			level.AddCube(m_CurrentTarget.x, m_CurrentTarget.y - 1, m_CurrentTarget.z);
		}
		if (camera.z > m_CurrentTarget.z && abs(m_CurrentRay.z - m_CurrentTarget.z - size) < epsilon)
		{
			level.AddCube(m_CurrentTarget.x, m_CurrentTarget.y, m_CurrentTarget.z + 1);
		}
		if (camera.z < m_CurrentTarget.z && abs(m_CurrentRay.z - m_CurrentTarget.z + size) < epsilon)
		{
			level.AddCube(m_CurrentTarget.x, m_CurrentTarget.y, m_CurrentTarget.z - 1);
		}
	}

}