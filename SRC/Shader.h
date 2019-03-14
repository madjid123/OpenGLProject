#pragma once

#include<string>
#include<unordered_map>
#include"glm/glm.hpp"
struct ShaderProgramSource {
	std::string VertexSource;
	std::string FragmentSource;
};

class shader
{
private:
	std::string m_FilePath;
	unsigned int m_RendererID;
	std::unordered_map<std::string, int> m_UniformLocationCashe;
public:
	shader(const std::string& filepath);
	~shader();

	void Bind()const;
	void Unbind()const;

	//set Uniforms 
	void SetUniformi(const std::string& name, int value);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniformMat4f(const std::string& name, const glm::mat4& mat);
	void SetUniform1f(const std::string& name, float value);
private:
	unsigned int CreateShader(const std::string& vertexshader, const std::string& fragmentshader);
	ShaderProgramSource ParseShader(const std::string& filepath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	int GetUniformLocation(const std::string& name);
};