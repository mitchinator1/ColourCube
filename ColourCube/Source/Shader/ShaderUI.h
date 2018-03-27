#ifndef SHADER_UI_H
#define SHADER_UI_H
#include <string>

#include "ShaderBase.h"

namespace Shader
{
	class ShaderUI : public ShaderBase
	{
	public:
		ShaderUI(const std::string& filepath = "Resources/Shader/UI.shader");
		~ShaderUI();

	};
}

#endif