#pragma once
#include <string>
#include <unordered_map>

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};


class Shader
{
public:
	Shader(const std::string &filePath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	void SetUniform4f(const std::string &name, float v0, float v1, float f2, float f3);

private:
	int GetUniformLocation(const std::string &name);
	ShaderProgramSource ParseShader(const std::string &filepath);
	unsigned int CompileShader(unsigned int type, const std::string &source);
	unsigned int CreateShaderProgram(const std::string &vertexShader, const std::string &fragmentShader);
	unsigned int m_shaderID;
	std::string m_filePath;
	// caching for uniforms
	std::unordered_map<std::string, int> m_uniformLocationCache;


};
