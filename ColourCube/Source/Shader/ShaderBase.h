#ifndef SHADER_BASE_H
#define SHADER_BASE_H
#include "ShaderProgram.h"

namespace Shader
{
	class ShaderBase : public ShaderProgram
	{
	private:
		std::unordered_map<std::string, int> m_UniformLocationCache;

	public:
		ShaderBase(const std::string& filename = "Basic") noexcept;
		~ShaderBase();

		void SetUniform1f(const std::string& name, float v);
		void SetUniform2f(const std::string& name, float v0, float v1);
		void SetUniform2f(const std::string& name, glm::vec2 v);
		void SetUniform3f(const std::string& name, float v0, float v1, float v2);
		void SetUniform3f(const std::string& name, glm::vec3 v);
		void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
		void SetUniform4f(const std::string& name, glm::vec4 v);
		void SetUniformMat4(const std::string& name, const glm::mat4 matrix);

	private:
		int GetUniformLocation(const std::string& name);
	};
}

#endif