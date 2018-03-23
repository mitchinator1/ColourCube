#include "ShaderFont.h"
#include <iostream>

namespace Shader
{
	ShaderFont::ShaderFont(const std::string& filepath)
		: ShaderBase(filepath)
	{
		
	}

	ShaderFont::~ShaderFont()
	{

	}

	void ShaderFont::LoadColour(glm::vec3& colour)
	{
		SetUniform3f("u_Colour", colour);
	}

	void ShaderFont::LoadTranslation(glm::vec2& translation)
	{
		SetUniform2f("u_Translation", translation);
	}
}