#pragma once
#include "GLFW/glfw3.h"
#include "GLM/glm.hpp"
#include "GLM/gtc/matrix_transform.hpp"

#include "BasicInput.h"
#include "Entity.h"

#include <vector>

class BasicCamera : public Entity
{
private:
	static unsigned int CameraID;
	unsigned int m_CameraID;

	float m_Yaw = -90.0f;
	float m_Pitch = 0.0f;
	float m_Zoom = 45.0f;
	float m_Speed = 0.025f;
	float m_Sensitivity = 0.25f;		/* Mouse Sensitivity */
	float m_NearFrustum = 0.1f;
	float m_FarFrustum = 200.0f;

	glm::vec3 m_Position;
	glm::vec3 m_Front = { 0.0f, 0.0f, -1.0f };
	glm::vec3 m_Right;
	glm::vec3 m_Up = { 0.0f, 1.0f, 0.0f };
	glm::vec3 m_WorldUp = { 0.0f, 1.0f, 0.0f };

public:
	BasicCamera(BasicInput* input, float pX = 0.0f, float pY = 0.0f, float pZ = 5.0f);
	~BasicCamera();

	void Update();
	unsigned int GetID() const { return m_CameraID; }
	void Move(MOVEMENT dir);

	unsigned int Bind(GLFWwindow* window);
	unsigned int Unbind();

	glm::mat4 GetProjectionMatrix(int width, int height);
	glm::mat4 GetViewMatrix();

private:
	BasicInput* m_Input;

	void UpdateCameraVectors();
	GLFWwindow* m_Window;
};