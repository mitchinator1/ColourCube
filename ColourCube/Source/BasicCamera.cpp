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

	for (int i = 0; i < m_Buttons.size(); i++)
		m_Buttons[i].isPressed = glfwGetKey(m_Window, m_Buttons[i].id);

	if(m_Buttons[0].isPressed) 
		m_Position += glm::normalize(glm::cross(m_WorldUp, m_Right)) * movementSpeed;

	if (m_Buttons[1].isPressed) 
		m_Position -= glm::normalize(glm::cross(m_WorldUp, m_Right)) * movementSpeed;

	if (m_Buttons[2].isPressed)
		m_Position -= glm::normalize(glm::cross(m_Front, m_Up)) * movementSpeed;

	if (m_Buttons[3].isPressed)
		m_Position += glm::normalize(glm::cross(m_Front, m_Up)) * movementSpeed;
	
	if (m_Buttons[4].isPressed)
		m_Position.y += movementSpeed;

	if (m_Buttons[5].isPressed)
		m_Position.y -= movementSpeed;

	UpdateCameraVectors();
}