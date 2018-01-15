#pragma once
#include "GLFW/glfw3.h"
#include "GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"

class BasicCamera
{
private:
	static unsigned int CameraID;
	unsigned int m_CameraID;

	float m_Yaw = -90.0f;
	float m_Pitch = 0.0f;
	float m_Speed = 1.0f;				/* Movement Speed */
	float m_Zoom = 45.0f;
	//float m_Sensitivity = 0.25f;		/* Mouse Sensitivity */
	float m_NearFrustum = 0.1f;
	float m_FarFrustum = 200.0f;

	glm::vec3 m_Position;
	glm::vec3 m_Front;
	glm::vec3 m_Right;
	glm::vec3 m_Up;
	glm::vec3 m_WorldUp = { 0.0f, 1.0f, 0.0f };

public:
	BasicCamera(float pX, float pY, float pZ);
	~BasicCamera();
	unsigned int GetID() const { return m_CameraID; }

	unsigned int Bind(GLFWwindow* window);
	unsigned int Unbind();

	glm::mat4 GetProjectionMatrix(int width, int height);
	glm::mat4 GetViewMatrix();
	void GetInput();

private:
	void UpdateCameraVectors();
	GLFWwindow* m_Window;

};