#pragma once

#include "GL/glew.h"
#include <string>
#include <unordered_map>
#include "GLM/glm.hpp"

struct ShaderProgramSource
{
	std::string vertexSource;
	std::string fragmentSource;
};

class Shader
{
private:
	int m_RendererID;
	std::unordered_map<std::string, int> m_UniformLocationCache;

public:
	Shader(const std::string& filepath = "Resources/Shaders/Basic.shader");
	~Shader();

	void Bind() const;
	void Unbind() const;
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniform4f(const std::string& name, glm::vec4 v);
	void SetUniformMat4(const std::string& name, glm::mat4 matrix);

private:
	ShaderProgramSource ParseShader(const std::string& filepath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	int GetUniformLocation(const std::string& name);
};