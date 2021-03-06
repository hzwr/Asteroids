#include "Shader.h"
#include "Renderer.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <malloc.h>

Shader::Shader(const std::string &filePath)
	: m_filePath(filePath)
	, m_shaderID(0)
{
	ShaderProgramSource source = ParseShader(filePath);
	m_shaderID = CreateShaderProgram(source.VertexSource, source.FragmentSource);
}

Shader::~Shader()
{
	GLCall(glDeleteProgram(m_shaderID));
}

void Shader::Bind() const
{
	GLCall(glUseProgram(m_shaderID));
}

void Shader::Unbind() const
{
	GLCall(glUseProgram(0));
}

void Shader::SetUniform1i(const std::string &name, int value)
{
	GLCall(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniform1f(const std::string &name, float value)
{
	GLCall(glUniform1f(GetUniformLocation(name), value));
}

void Shader::SetUniform4f(const std::string &name, float f0, float f1, float f2, float f3)
{
	GLCall(glUniform4f(GetUniformLocation(name), f0, f1, f2, f3));
}

void Shader::SetUniformMat4f(const std::string &name, const Matrix4 &mat)
{
	GLCall(glUniformMatrix4fv(
		GetUniformLocation(name),
		1,	// number of matrices
		GL_TRUE, // set to true if using row vector
		mat.GetAsFloatPtr()
		))
}

void Shader::SetUniform3fv(const std::string &name, const Vector3 &vector)
{
	GLCall(glUniform3fv(GetUniformLocation(name), 1, vector.GetAsFloatPtr()));
}

int Shader::GetUniformLocation(const std::string &name)
{
	auto iter = m_uniformLocationCache.find(name);
	if (iter != m_uniformLocationCache.end())
	{
		return iter->second;
	}

	GLCall(int location = glGetUniformLocation(m_shaderID, name.c_str()));
	if (location == -1)
	{
		std::cout << "Warning: uniform '" << name << "' does not exist" << std::endl;
	}

	m_uniformLocationCache.emplace(name, location);

	return location;
}

ShaderProgramSource Shader::ParseShader(const std::string &filepath)
{
	std::ifstream stream(filepath); // Open the file

	enum class ShaderType
	{
		NONE = -1,
		VERTEX = 0,
		FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;

	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos)
			{
				type = ShaderType::FRAGMENT;
			}
		}
		else
		{
			ss[(int)type] << line << '\n';
		}
	}

	return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::CompileShader(unsigned int type, const std::string &source)
{
	unsigned int id = glCreateShader(type);
	const char *src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	// Error handling
	int result;
	int errcode;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		__try
		{
			char *message = (char *)_malloca(length * sizeof(char));
			glGetShaderInfoLog(id, length, &length, message);
			std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex " : "fragment ") << "shader" << std::endl;
			std::cout << message << std::endl;
			glDeleteShader(id);
			_freea(message);
		}
		__except ((GetExceptionCode() == STATUS_STACK_OVERFLOW) ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH)
		{
			errcode = _resetstkoflw();
			// TODO: https://docs.microsoft.com/en-us/cpp/cpp/try-except-statement?view=msvc-160
			// https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/resetstkoflw?view=msvc-160
		}
		return 0;
	}

	return id;
}

unsigned int Shader::CreateShaderProgram(const std::string &vertexShader, const std::string &fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;

}
