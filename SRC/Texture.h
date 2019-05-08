#pragma once
#include"Renderer.h"

class Texture {
private:
	GLuint m_RendererID;
	std::string m_FilePath;
	GLubyte* m_LocalBuffer;
	int m_Width, m_Heigth, m_BPP;
public:
	Texture(std::string path);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	inline int GetWidth() { return m_Width; };
	inline int GetHeigth() { return m_Heigth; };
};