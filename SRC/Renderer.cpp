#include "Renderer.h"
#include<iostream>


void GlClearError() {
	while (glGetError() != GL_NO_ERROR);
}
bool GlLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[openGL] error ( " << error << " )" <<
			function << " " << file << " : " << line << std::endl;
		return false;
	}
	return true;

}

void Renderer::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT);
}
void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const shader& Shader) const
{
	va.Bind();
	ib.Bind();
	Shader.Bind();
	glCall(glDrawElements(GL_TRIANGLES, ib.getcount(), GL_UNSIGNED_INT, nullptr));

}