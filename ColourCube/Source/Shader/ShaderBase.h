#pragma once
#include "ShaderProgram.h"

namespace Shader
{
	class ShaderBase : public ShaderProgram
	{
	private:
		std::unordered_map<std::string, int> m_UniformLocationCache;

	public:
		ShaderBase(const std::string& filepath = "Resources/Shader/Basic.shader");
		~ShaderBase();

		void SetUniform2f(const std::string& name, float v0, float v1);
		void SetUniform2f(const std::string& name, glm::vec2 v);
		void SetUniform3f(const std::string& name, float v0, float v1, float v2);
		void SetUniform3f(const std::string& name, glm::vec3 v);
		void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
		void SetUniform4f(const std::string& name, glm::vec4 v);
		void SetUniformMat4(const std::string& name, glm::mat4 matrix);

	private:
		int GetUniformLocation(const std::string& name);
	};
}