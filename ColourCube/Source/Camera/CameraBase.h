#ifndef CAMERA_BASE_H
#define CAMERA_BASE_H
#include <vector>
#include <memory>
#include "GLM/glm.hpp"

#include "../Entity.h"

struct Display;
namespace Input { class InputBase; }

namespace Camera
{
	class CameraBase : public Entity
	{
	private:
		static unsigned int s_CameraID;
		unsigned int m_CameraID;

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

		glm::mat4 m_ModelMatrix;

		std::unique_ptr<Input::InputBase> m_Input;

		glm::vec3 m_Target;
		float m_FocusDistance = 5.0f;
		bool m_Focused = false;

		float m_ProjWidth = 0.0f;
		float m_ProjHeight = 0.0f;

	public:
		CameraBase(std::unique_ptr<Input::InputBase> input, std::shared_ptr<Display> display, float pX = 0.0f, float pY = 0.0f, float pZ = 5.0f);
		CameraBase(float pX = 0.0f, float pY = 0.0f, float pZ = 5.0f) noexcept;
		~CameraBase();

		void HandleEvents() override;
		void Update() override;
		void Action(Command command) override;
		glm::vec3& GetPosition() override { return m_Position; }
		glm::mat4& GetModelMatrix() override { return m_ModelMatrix; }

		inline unsigned int GetID() const { return m_CameraID; }

		void Target(glm::vec3& position);
		void UnTarget();

		glm::mat4 GetProjectionMatrix();
		glm::mat4 GetViewMatrix();

	private:
		void UpdateCameraVectors();

	};
}

#endif