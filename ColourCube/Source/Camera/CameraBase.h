#ifndef CAMERA_BASE_H
#define CAMERA_BASE_H
#include <vector>
#include <memory>
#include "../Entity/EntityBase.h"

struct Display;
namespace Input { class InputBase; }

namespace Camera
{
	class CameraBase : public Entity::EntityBase
	{
	private:
		float m_Yaw			= -90.0f;
		float m_Pitch		= 0.0f;
		float m_Zoom		= 45.0f;
		//float m_Speed		= 0.025f;
		//float m_Sensitivity = 0.25f;
		float m_NearFrustum = 0.1f;
		float m_FarFrustum	= 25.0f;

		glm::vec3 m_Front;
		glm::vec3 m_Right;
		glm::vec3 m_Up		= { 0.0f, 1.0f, 0.0f };
		glm::vec3 m_WorldUp = { 0.0f, 1.0f, 0.0f };
		
		float m_ProjWidth	= 0.0f;
		float m_ProjHeight	= 0.0f;

		//glm::vec3* m_Target = nullptr;
		float m_FocusDistance = 5.0f;

		std::unique_ptr<Input::InputBase> m_Input;

	public:
		CameraBase(std::unique_ptr<Input::InputBase> input, std::shared_ptr<Display> display, float pX = 0.0f, float pY = 0.0f, float pZ = 5.0f);
		CameraBase(std::shared_ptr<Display> display, float pX = 0.0f, float pY = 0.0f, float pZ = 5.0f);
		CameraBase(float pX = 0.0f, float pY = 0.0f, float pZ = 5.0f) noexcept;
		~CameraBase();

		void HandleEvents()				override;
		void Update()					override;

		void AddInput(std::unique_ptr<Input::InputBase> input);

		void Target(glm::vec3& position);
		void UnTarget();

		glm::mat4 GetProjectionMatrix();
		glm::mat4 GetViewMatrix();

	private:
		void UpdateCameraVectors();

	};
}

#endif