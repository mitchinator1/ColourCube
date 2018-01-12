#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <string>

struct ShaderProgramSource
{
	std::string vertexSource;
	std::string fragmentSource;
};

class Shader
{
private:
	int m_RendererID;
public:
	Shader(const std::string& filepath = "Resources/Shaders/Basic.shader");
	~Shader();

	void Bind() const;
	void Unbind() const;

private:
	ShaderProgramSource ParseShader(const std::string& filepath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
};