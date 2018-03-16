#include "CameraBase.h"
#include "GLM/gtc/matrix_transform.hpp"
#include <iostream>

unsigned int Camera::CameraBase::s_CameraID = 0;

namespace Camera
{
	CameraBase::CameraBase(Input::InputBase* input, float pX, float pY, float pZ)
		: m_Position({ pX, pY, pZ }), m_Input(input), m_FocusObject(nullptr),
		m_ProjWidth(1800), m_ProjHeight(1200) //TODO: Abstract out 1800 and 1200
	{
		m_CameraID = s_CameraID++;
		UpdateCameraVectors();
	}

	CameraBase::CameraBase(float pX, float pY, float pZ)
		: m_Position({ pX, pY, pZ }), m_Input(nullptr), m_FocusObject(nullptr)
	{
		m_CameraID = s_CameraID++;
		UpdateCameraVectors();
	}

	CameraBase::~CameraBase()
	{
		delete m_Input;
	}

	void CameraBase::HandleEvents()
	{
		m_Input->HandleEvents(*this);
	}

	void CameraBase::Update()
	{
		m_Input->Update(*this);
		UpdateCameraVectors();
	}

	void CameraBase::Action(Command command)
	{
		switch (command)
		{
		case Command::FORWARD:
			//m_Position += glm::normalize(glm::cross(m_WorldUp, m_Right)) * m_Speed;
			if (m_FocusDistance > 0.0f)
				m_FocusDistance -= 0.01f;
			break;
		case Command::BACKWARD:
			//m_Position -= glm::normalize(glm::cross(m_WorldUp, m_Right)) * m_Speed;
			if (m_FocusDistance < 10.0f)
				m_FocusDistance += 0.01f;
			break;
		case Command::LEFT:
			m_Position -= glm::normalize(glm::cross(m_Front, m_Up)) * m_Speed;
			m_Yaw += 0.3f;
			break;
		case Command::RIGHT:
			m_Position += glm::normalize(glm::cross(m_Front, m_Up)) * m_Speed;
			m_Yaw -= 0.3f;
			break;
		case Command::UP:
			if (m_FocusObject)
			{
				m_Position.y += m_Speed;
				//m_Pitch -= 0.3f;
			}
			else
				m_Position.y += m_Speed;
			break;
		case Command::DOWN:
			if (m_FocusObject)
			{
				m_Position.y -= m_Speed;
				//m_Pitch += 0.3f;
			}
			break;
		}
	}

	glm::mat4 CameraBase::GetProjectionMatrix()
	{
		return glm::perspective(glm::radians(m_Zoom), m_ProjWidth / m_ProjHeight, m_NearFrustum, m_FarFrustum);
	}

	glm::mat4 CameraBase::GetViewMatrix()
	{
		//if (m_FocusObject)
		//	return glm::lookAt(m_Position, GetFocusCoords(), m_Up);
		//else
		return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
	}

	void CameraBase::UpdateCameraVectors()
	{
		if (m_Pitch > 89.0f)
			m_Pitch = 89.0f;
		if (m_Pitch < -89.0f)
			m_Pitch = -89.0f;

		//if (m_FocusObject)
	//		m_Position = (glm::normalize(m_Position) * glm::vec3{ m_FocusDistance, m_FocusDistance, m_FocusDistance });

		glm::vec3 front;
		front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		front.y = sin(glm::radians(m_Pitch));
		front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));

		m_Front = glm::normalize(front);
		m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
		m_Up = glm::normalize(glm::cross(m_Right, m_Front));
	}

	void CameraBase::Target(Entity* targetObject)
	{
		m_FocusObject = targetObject;
		m_Position.x = m_FocusObject->GetPosition().x / 2.0f;
		m_Position.y = m_FocusObject->GetPosition().y / 2.0f;
		m_Position.z = m_FocusObject->GetPosition().z + m_FocusDistance;
	}

	void CameraBase::UnTarget()
	{
		m_FocusObject = nullptr;
	}

}