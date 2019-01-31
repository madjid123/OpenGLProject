#pragma once
#include<string>
struct ShaderProgramSource {
	std::string VertexSource;
	std::string FragmentSource;
};

class shader
{
private :
	std::string m_FilePath;
	unsigned int m_RendererID;
public :
	shader(const std::string& filepath);
	~shader();

	void Bind()const;
	void Unbind()const;

	//set Uniforms 
	void SetUniform4(const std::string& name, float v0, float v1, float v2, float v3);
private:
	unsigned int CreateShader(const std::string& vertexshader, const std::string& fragmentshader);
	ShaderProgramSource ParseShader(const std::string& filepath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
 int GetUniformLocation(const std::string& name);
};