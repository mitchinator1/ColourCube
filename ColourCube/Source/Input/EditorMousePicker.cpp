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
		m_SelectionFace = Face::TOP;
	}

	void EditorMousePicker::HandleEvents()
	{
		MouseBase::GetMouseInput();
		CalculateMouseRay();
	}

	void EditorMousePicker::Update(Level& level)
	{
		//TODO: Fix faces being added/removed.
		if (m_ShowSelection)
		{
			if (m_AddCubeToggled)
			{
				if (m_TempCube)
				{
					if (!MouseRayIntersects(level) || !TempCubeSelected())
					{
						auto& target = m_TempCube->GetPosition();
						level.RemoveCube(target.x, target.y, target.z);
						m_TempCube = nullptr;
						m_Selection = { 0.0f, 0.0f, 0.0f };
					}
				}
				else if (MouseRayIntersects(level))
				{
					ShowSelection(level);
				}
			}
			else
			{
				if (m_TempCube)
				{
					if (!MouseRayIntersects(level) || m_TempCube->GetPosition() != m_CurrentTarget)
					{
						m_TempCube->SetAlpha(1.0f)->SetColour(1.0f, 1.0f, 1.0f);
						m_TempCube = nullptr;
						level.ForceUpdate();
					}
				}
				else if (MouseRayIntersects(level))
				{
					m_TempCube = level.GetCube(m_CurrentTarget.x, m_CurrentTarget.y, m_CurrentTarget.z);
					if (m_TempCube)
					{
						m_TempCube->SetAlpha(0.5f)->SetColour(0.7f, 0.3f, 0.2f);
						level.FillFaces(m_CurrentTarget.x, m_CurrentTarget.y, m_CurrentTarget.z);
					}
				}
			}
		}
		if (m_Toggled)
		{
			//ConfirmChange(level);
			if (m_AddCubeToggled)
			{
				AddCube(level);
			}
			else
			{
				if (m_TempCube)
				{
					level.RemoveCube(m_CurrentTarget.x, m_CurrentTarget.y, m_CurrentTarget.z);
					m_TempCube = nullptr;
				}
			}
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
		m_Targets = {
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
		};

		for (auto& cube : cubes)
		{
			if (cube->IsGhost())
				continue;
			m_Targets.emplace_back(cube->GetPosition());
		}
	}

	void EditorMousePicker::ShowSelection(Level& level)
	{
		const float epsilon = 0.015f;
		const float size	= 0.5f;
		const float alpha	= 0.5f;
		const auto& camera	= m_Camera->GetPosition();

		if (camera.y > m_CurrentTarget.y && abs(m_CurrentRay.y - m_CurrentTarget.y - size) < epsilon)
		{
			m_TempCube = level.AddTempCube(m_CurrentTarget.x, m_CurrentTarget.y + 1, m_CurrentTarget.z)
				->SetGhost()->SetAlpha(alpha)->SetColour(0.3f, 0.7f, 0.2f);
			m_Selection = m_CurrentTarget;
			m_SelectionFace = Face::TOP;
			return;
		}
		if (camera.y < m_CurrentTarget.y && abs(m_CurrentRay.y - m_CurrentTarget.y + size) < epsilon)
		{
			m_TempCube = level.AddTempCube(m_CurrentTarget.x, m_CurrentTarget.y - 1, m_CurrentTarget.z)
				->SetGhost()->SetAlpha(alpha)->SetColour(0.3f, 0.7f, 0.2f);
			m_Selection = m_CurrentTarget;
			m_SelectionFace = Face::BOTTOM;
			return;
		}
		if (camera.x > m_CurrentTarget.x && abs(m_CurrentRay.x - m_CurrentTarget.x - size) < epsilon)
		{
			m_TempCube = level.AddTempCube(m_CurrentTarget.x + 1, m_CurrentTarget.y, m_CurrentTarget.z)
				->SetGhost()->SetAlpha(alpha)->SetColour(0.3f, 0.7f, 0.2f);
			m_Selection = m_CurrentTarget;
			m_SelectionFace = Face::EAST;
			return;
		}
		if (camera.x < m_CurrentTarget.x && abs(m_CurrentRay.x - m_CurrentTarget.x + size) < epsilon)
		{
			m_TempCube = level.AddTempCube(m_CurrentTarget.x - 1, m_CurrentTarget.y, m_CurrentTarget.z)
				->SetGhost()->SetAlpha(alpha)->SetColour(0.3f, 0.7f, 0.2f);
			m_Selection = m_CurrentTarget;
			m_SelectionFace = Face::WEST;
			return;
		}
		if (camera.z > m_CurrentTarget.z && abs(m_CurrentRay.z - m_CurrentTarget.z - size) < epsilon)
		{
			m_TempCube = level.AddTempCube(m_CurrentTarget.x, m_CurrentTarget.y, m_CurrentTarget.z + 1)
				->SetGhost()->SetAlpha(alpha)->SetColour(0.3f, 0.7f, 0.2f);
			m_Selection = m_CurrentTarget;
			m_SelectionFace = Face::SOUTH;
			return;
		}
		if (camera.z < m_CurrentTarget.z && abs(m_CurrentRay.z - m_CurrentTarget.z + size) < epsilon)
		{
			m_TempCube = level.AddTempCube(m_CurrentTarget.x, m_CurrentTarget.y, m_CurrentTarget.z - 1)
				->SetGhost()->SetAlpha(alpha)->SetColour(0.3f, 0.7f, 0.2f);
			m_Selection = m_CurrentTarget;
			m_SelectionFace = Face::NORTH;
			return;
		}
	}

	void EditorMousePicker::AddCube(Level& level)
	{
		//Set Temp cube to be permanent
		if (m_TempCube)
		{
			m_TempCube->SetGhost(false)->SetAlpha(1.0f)->SetColour(1.0f, 1.0f, 1.0f);
			level.AddCube(m_TempCube);
			m_TempCube = nullptr;
		}
	}

	bool EditorMousePicker::TempCubeSelected()
	{
		if (m_CurrentTarget != m_Selection)
			return false;

		if (GetSelectedFace() != m_SelectionFace)
			return false;

		return true;
	}

	Face EditorMousePicker::GetSelectedFace()
	{
		const float size = 0.5f;
		const float epsilon = 0.015f;
		const auto& camera = m_Camera->GetPosition();

		if (camera.y > m_CurrentTarget.y && abs(m_CurrentRay.y - m_CurrentTarget.y - size) < epsilon)
		{
			return Face::TOP;
		}
		if (camera.y < m_CurrentTarget.y && abs(m_CurrentRay.y - m_CurrentTarget.y + size) < epsilon)
		{
			return Face::BOTTOM;
		}
		if (camera.x > m_CurrentTarget.x && abs(m_CurrentRay.x - m_CurrentTarget.x - size) < epsilon)
		{
			return Face::EAST;
		}
		if (camera.x < m_CurrentTarget.x && abs(m_CurrentRay.x - m_CurrentTarget.x + size) < epsilon)
		{
			return Face::WEST;
		}
		if (camera.z > m_CurrentTarget.z && abs(m_CurrentRay.z - m_CurrentTarget.z - size) < epsilon)
		{
			return Face::SOUTH;
		}
		if (camera.z < m_CurrentTarget.z && abs(m_CurrentRay.z - m_CurrentTarget.z + size) < epsilon)
		{
			return Face::NORTH;
		}

		return Face::TOP;
	}

}