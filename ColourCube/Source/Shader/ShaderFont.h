#pragma once
#include <string>

#include "ShaderBase.h"

namespace Shader
{
	class ShaderFont : public ShaderBase
	{
	public:
		ShaderFont(const std::string& filepath = "Resources/Shader/Basic.shader");
		~ShaderFont();

		void LoadColour(glm::vec3& colour);
		void LoadTranslation(glm::vec2& translation);
	};
}