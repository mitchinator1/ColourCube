#include "ShaderBase.h"
#include "GL/glew.h"
#include <iostream>

namespace Shader
{
	ShaderBase::ShaderBase(const std::string& filename) noexcept
		: ShaderProgram("Resources/Shader/" + filename + ".shader")
	{

	}

	ShaderBase::~ShaderBase()
	{
		
	}

	void ShaderBase::SetUniform1f(const std::string& name, float v)
	{
		glUniform1f(GetUniformLocation(name), v);
	}

	void ShaderBase::SetUniform2f(const std::string& name, float v0, float v1)
	{
		glUniform2f(GetUniformLocation(name), v0, v1);
	}

	void ShaderBase::SetUniform2f(const std::string& name, glm::vec2 v)
	{
		glUniform2f(GetUniformLocation(name), v.x, v.y);
	}

	void ShaderBase::SetUniform3f(const std::string& name, float v0, float v1, float v2)
	{
		glUniform3f(GetUniformLocation(name), v0, v1, v2);
	}

	void ShaderBase::SetUniform3f(const std::string& name, glm::vec3 v)
	{
		glUniform3f(GetUniformLocation(name), v.x, v.y, v.z);
	}

	void ShaderBase::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
	{
		glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
	}

	void ShaderBase::SetUniform4f(const std::string& name, glm::vec4 v)
	{
		glUniform4f(GetUniformLocation(name), v.x, v.y, v.z, v.w);
	}

	void ShaderBase::SetUniformMat4(const std::string& name, glm::mat4 matrix)
	{
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
	}

	int ShaderBase::GetUniformLocation(const std::string& name)
	{
		if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
			return m_UniformLocationCache[name];

		int location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location == -1)
			std::cout << "Shader::Uniform '" << name << "' not found." << std::endl;
		m_UniformLocationCache[name] = location;
		return location;
	}
}