#include "rendrer.h"
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