#pragma once
#include "GLFW/glfw3.h"
#include "GLM/glm.hpp"

#include "../Input/InputBase.h"
#include "../Entity.h"

#include <vector>

namespace Camera
{
	class CameraBase : public Entity
	{
	private:
		static unsigned int s_CameraID;
		unsigned int m_CameraID;

		float m_ProjWidth;
		float m_ProjHeight;

		float m_Yaw = -90.0f;
		float m_Pitch = 0.0f;
		float m_Zoom = 45.0f;
		float m_Speed = 0.025f;
		//float m_Sensitivity = 0.25f;
		float m_NearFrustum = 0.1f;
		float m_FarFrustum = 100.0f;

		glm::vec3 m_Position;
		glm::vec3 m_Front = { 0.0f, 0.0f, -1.0f };
		glm::vec3 m_Right;
		glm::vec3 m_Up = { 0.0f, 1.0f, 0.0f };
		glm::vec3 m_WorldUp = { 0.0f, 1.0f, 0.0f };

		float m_FocusDistance = 5.0f;

		Input::InputBase* m_Input;
		Entity* m_FocusObject;

	public:
		CameraBase(Input::InputBase* input, float pX = 0.0f, float pY = 0.0f, float pZ = 5.0f);
		CameraBase(float pX = 0.0f, float pY = 0.0f, float pZ = 0.0f);
		~CameraBase();

		void HandleEvents();
		void Update();
		void Action(Command command);
		glm::vec3& GetPosition() { return m_Position; }

		inline unsigned int GetID() const { return m_CameraID; }

		void Target(Entity* targetObject);
		void UnTarget();

		glm::mat4 GetProjectionMatrix();
		glm::mat4 GetViewMatrix();

	private:
		void UpdateCameraVectors();
		glm::vec3 GetFocusCoords() { return m_FocusObject->GetPosition(); }

	};
}