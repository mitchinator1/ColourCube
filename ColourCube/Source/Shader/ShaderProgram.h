#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H
#include "GLM/glm.hpp"
#include <string>
#include <unordered_map>

namespace Shader
{
	struct ShaderProgramSource
	{
		std::string vertexSource;
		std::string fragmentSource;
	};

	class ShaderProgram
	{
	private:
		std::unordered_map<std::string, int> m_UniformLocationCache;

	protected:
		int m_RendererID;

	public:
		ShaderProgram(const std::string& filepath = "Resources/Shader/Basic.shader") noexcept;
		~ShaderProgram();

		void Bind() const;
		void Unbind() const;

	private:
		ShaderProgramSource ParseShader(const std::string& filepath);
		unsigned int CompileShader(unsigned int type, const std::string& source);
		unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

	};
}

#endif