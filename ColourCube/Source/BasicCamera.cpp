#include "BasicCamera.h"
#include "GLM/gtc/matrix_transform.hpp"
#include <iostream>

unsigned int BasicCamera::s_CameraID = 0;

BasicCamera::BasicCamera(BasicInput* input, float pX, float pY, float pZ)
	: m_Position({ pX, pY, pZ }), m_Input(input)
{
	m_CameraID = s_CameraID++;
	UpdateCameraVectors();
}

BasicCamera::BasicCamera(float pX, float pY, float pZ)
	: m_Position({ pX, pY, pZ }), m_Input(nullptr)
{
	m_CameraID = s_CameraID++;
	UpdateCameraVectors();
}

BasicCamera::~BasicCamera()
{
	delete m_Input;
}

void BasicCamera::HandleEvents()
{
	m_Input->HandleEvents();
}

void BasicCamera::Update()
{
	m_Input->Update(*this);
	UpdateCameraVectors();
}

void BasicCamera::Action(Command command)
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

glm::mat4 BasicCamera::GetProjectionMatrix(int width, int height)
{
	return glm::perspective(glm::radians(m_Zoom), (float)width / (float)height, m_NearFrustum, m_FarFrustum);
}

glm::mat4 BasicCamera::GetViewMatrix()
{
	//if (m_FocusObject)
	//	return glm::lookAt(m_Position, GetFocusCoords(), m_Up);
	//else
		return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
}

void BasicCamera::UpdateCameraVectors()
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

void BasicCamera::Target(Entity* targetObject)
{
	m_FocusObject = targetObject;
}

void BasicCamera::UnTarget()
{
	m_FocusObject = nullptr;
}