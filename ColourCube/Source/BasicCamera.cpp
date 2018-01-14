#include "BasicCamera.h"

BasicCamera::BasicCamera(float pX, float pY, float pZ)
	: m_Position({ pX, pY, pZ }), m_Front({0.0f, 0.0f, -1.0f}), m_Up({0.0f, 1.0f, 0.0f})
{
	UpdateCameraVectors();
}

BasicCamera::~BasicCamera()
{

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