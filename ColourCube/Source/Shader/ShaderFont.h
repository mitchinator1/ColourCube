#ifndef SHADER_FONT_H
#define SHADER_FONT_H
#include <string>

#include "ShaderBase.h"

namespace Shader
{
	class ShaderFont : public ShaderBase
	{
	public:
		ShaderFont(const std::string& filepath = "Resources/Shader/Font.shader");
		~ShaderFont();

		void LoadColour(glm::vec3& colour);
		void LoadTranslation(glm::vec2& translation);
	};
}

#endif