#include"Shader.h"
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include"Renderer.h"

shader::shader(const std::string& filepath)
	: m_FilePath(filepath), m_RendererID(0)
{
	ShaderProgramSource source = ParseShader(filepath);
	m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
}
shader::~shader()
{
	glCall(glDeleteProgram(m_RendererID));
}

unsigned int shader::CompileShader(unsigned int type, const std::string& source)
{
	glCall(unsigned int id = glCreateShader(type));
	const char* src = source.c_str();
	glCall(glShaderSource(id, 1, &src, nullptr));
	glCall(glCompileShader(id));

	int result;
	glCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));

	if (result == GL_FALSE)
	{
		int length;
		glCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char* message = (char*)alloca(length * sizeof(char));
		glCall(glGetShaderInfoLog(id, length, &length, message));
		std::cout << "Failed to compile Shader !!" << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader" <<
			std::endl;
		std::cout << message << std::endl;
		glCall(glDeleteShader(id));
		return 0;
	}
	return id;
}
unsigned int shader::CreateShader(const std::string& vertexshader, const std::string& fragmentshader) {
	glCall(unsigned int program = glCreateProgram());
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexshader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentshader);

	glCall(glAttachShader(program, vs));
	glCall(glAttachShader(program, fs));
	glCall(glLinkProgram(program));
	glCall(glValidateProgram(program));
	glCall(glDeleteShader(vs));
	glCall(glDeleteShader(fs));
	return program;
}
ShaderProgramSource shader::ParseShader(const std::string& filepath)
{

	std::ifstream stream(filepath);
	enum class shadertype
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};
	std::string line;
	std::stringstream ss[2];
	shadertype type = shadertype::NONE;

	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{//set mode to vertex
				type = shadertype::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos) {
				//set mode to fragment
				type = shadertype::FRAGMENT;
			}
		}
		else
			ss[(int)type] << line << '\n';
	}
	return { ss[0].str() , ss[1].str() };
}
void shader::Bind() const
{
	glCall(glUseProgram(m_RendererID));
}
void shader::Unbind()const
{
	glCall(glUseProgram(0));
}
void shader::SetUniform1f(const std::string& name, float value)
{
	glCall(glUniform1f(GetUniformLocation(name), value));

}
void shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	glCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));

}
void shader::SetUniformi(const std::string& name, int value)
{
	glCall(glUniform1i(GetUniformLocation(name), value));
}
void shader::SetUniformMat4f(const std::string& name, const glm::mat4& mat)
{
	glCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &mat[0][0]));
}
int shader::GetUniformLocation(const std::string& name)
{
	if (m_UniformLocationCashe.find(name) != m_UniformLocationCashe.end())
		return m_UniformLocationCashe[name];

	glCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));

	if (location == -1)
	{
		std::cout << "Warning !! Uniform : " << name << " doesn't exist " << std::endl;
	}
	m_UniformLocationCashe[name] = location;
	return location;
}