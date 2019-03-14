#include"IndexBuffer.h"
#include "Renderer.h"
IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
	: m_count(count)
{
	ASSERT(sizeof(GLuint) == sizeof(unsigned int));
	glCall(glGenBuffers(1, &m_rendererID));
	glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID));
	glCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW));
}
IndexBuffer::~IndexBuffer()
{
	glCall(glDeleteBuffers(1, &m_rendererID));
}
void IndexBuffer::Bind() const
{
	glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID));
}
void IndexBuffer::unbind() const
{
	glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}