#pragma once
#include <memory>
#include "../VertexBuffer.h"
#include"../IndexBuffer.h"
#include "../VertexBufferLayout.h"
#include"../VertexArray.h"
#include "../Texture.h"
#include "test.h"
namespace test {
	
	class TestTexture2D : public test {
	public:
		TestTexture2D() ;
		~TestTexture2D();
		
		
		void OnUpdate(float DateTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		glm::vec3 m_translationA, m_translationB;
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<shader> m_shader;
		glm::mat4 m_proj, m_view;
		std::unique_ptr<Texture> m_Texture;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;

	};
}