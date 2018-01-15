#include "BasicCamera.h"
#include <iostream>

unsigned int BasicCamera::CameraID = 0;

BasicCamera::BasicCamera(float pX, float pY, float pZ)
	: m_Position({ pX, pY, pZ }), m_Front({0.0f, 0.0f, -1.0f}), m_Up({0.0f, 1.0f, 0.0f})
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

void BasicCamera::GetInput()
{
	float movementSpeed = 0.01f;

	int keyPressed = glfwGetKey(m_Window, GLFW_PRESS);
	std::cout << keyPressed << std::endl;
	switch (keyPressed)
	{
	case GLFW_KEY_W:			m_Position += glm::normalize(glm::cross(m_WorldUp, m_Right)) * movementSpeed;
		break;
	case GLFW_KEY_S:			m_Position -= glm::normalize(glm::cross(m_WorldUp, m_Right)) * movementSpeed;
		break;
	case GLFW_KEY_A:			m_Position -= glm::normalize(glm::cross(m_Front, m_Up)) * movementSpeed;
		break;
	case GLFW_KEY_D:			m_Position += glm::normalize(glm::cross(m_Front, m_Up)) * movementSpeed;
		break;
	case GLFW_KEY_LEFT_SHIFT:	m_Position.y += movementSpeed;
		break;
	case GLFW_KEY_SPACE:		m_Position.y -= movementSpeed;
		break;
	default:
		break;
	}

	UpdateCameraVectors();
}