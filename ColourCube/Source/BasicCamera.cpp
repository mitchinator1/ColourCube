#include "BasicCamera.h"
#include <iostream>

unsigned int BasicCamera::CameraID = 0;

BasicCamera::BasicCamera(BasicInput* input, float pX, float pY, float pZ)
	: m_Position({ pX, pY, pZ }), m_Input(input)
{
	m_CameraID = CameraID++;
	UpdateCameraVectors();
}

BasicCamera::~BasicCamera()
{

}

unsigned int BasicCamera::Bind(GLFWwindow* window)
{
	m_Window = window;
	m_Input->Bind(window);
	return m_CameraID;
}

unsigned int BasicCamera::Unbind()
{
	m_Window = nullptr;
	return m_CameraID;
}

glm::mat4 BasicCamera::GetProjectionMatrix(int width, int height)
{
	return glm::perspective(glm::radians(m_Zoom), (float)width / (float)height, m_NearFrustum, m_FarFrustum);
}

glm::mat4 BasicCamera::GetViewMatrix()
{
	return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
}

void BasicCamera::UpdateCameraVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	front.y = sin(glm::radians(m_Pitch));
	front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));

	m_Front = glm::normalize(front);
	m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
	m_Up = glm::normalize(glm::cross(m_Right, m_Front));
}

void BasicCamera::Update()
{
	float movementSpeed = 0.01f;
	m_Input->Update(*this);
	UpdateCameraVectors();
}

void BasicCamera::Move(MOVEMENT dir)
{
	switch (dir)
	{
	case MOVEMENT::FORWARD: m_Position += glm::normalize(glm::cross(m_WorldUp, m_Right)) * m_Speed;
		break;
	case MOVEMENT::BACKWARD: m_Position -= glm::normalize(glm::cross(m_WorldUp, m_Right)) * m_Speed;
		break;
	case MOVEMENT::LEFT: m_Position -= glm::normalize(glm::cross(m_Front, m_Up)) * m_Speed;
		break;
	case MOVEMENT::RIGHT: m_Position += glm::normalize(glm::cross(m_Front, m_Up)) * m_Speed;
		break;
	case MOVEMENT::UP: m_Position.y += m_Speed;
		break;
	case MOVEMENT::DOWN: m_Position.y -= m_Speed;
		break;
	}
}
