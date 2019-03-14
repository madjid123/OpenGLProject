#pragma once
class IndexBuffer {

private:
	unsigned int m_rendererID;
	unsigned int m_count;

public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void unbind() const;

	inline unsigned int getcount() const { return m_count; }
};