#include "TestTexture2D.h"
#include<iostream>
#include "../Renderer.h"
#include "../vendor/imgui/imgui.h"
#include "../VertexBufferLayout.h"
#include "../VertexBuffer.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include"imgui/imgui.h"
#include"imgui/imgui_impl_glfw_gl3.h"
#include"../texture.h"
#include <memory>
namespace test {

	TestTexture2D::TestTexture2D() 
	  :	
		m_translationA{ 200, 200 , 0}, 
		m_translationB{ 400, 200 , 0} ,
		m_proj{ glm::ortho<float>(0.0, 960.0, 0.0, 540.0, -1.0, 1.0) },
		m_view{ glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)) }
	{
		float position[] = {
					-50.0f,  -50.0f, 0.0f, 0.0f, //0
					 50.0f,  -50.0f, 1.0f, 0.0f, //1
					 50.0f,   50.0f, 1.0f, 1.0f, //2
					-50.0f,   50.0f, 0.0f, 1.0f  //3
		};

		//repeated indecies of the square (optimized method)
		unsigned int indecies[] = {
			0,1,2,
			2,3,0
		};
		glCall(glEnable(GL_BLEND));
		glCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		m_shader = std::make_unique <shader>("res/shader/vbasic.shader");
		m_VAO	= std::make_unique<VertexArray>();
		m_VertexBuffer = std::make_unique<VertexBuffer>(position, 4 * 4 * sizeof(float));

		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);
		m_VAO->AddBuffer(*m_VertexBuffer, layout);
		m_IndexBuffer = std::make_unique<IndexBuffer>(indecies, 6);
		

		std::cout << glGetString(GL_VERSION) << std::endl;

		
		m_shader->Bind();
		
		m_Texture = std::make_unique<Texture>("res/textures/h.png");
	

		//shader.SetUniform4f("u_color", 0.1f, 0.5f, 0.8f, 1.0f);

		m_shader->SetUniformi("u_Texture", 0);
	}

	TestTexture2D::~TestTexture2D()
	{

	}

	void TestTexture2D::OnUpdate(float DateTime)
	{

	}

	void TestTexture2D::OnRender()
	{
		glCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		glCall(glClear(GL_COLOR_BUFFER_BIT));
		
		Renderer Renderer;
		m_Texture->Bind();
		{

			glm::mat4 model = glm::translate(glm::mat4(1.0f),m_translationA);
			glm::mat4 mvp = m_proj * m_view * model;
			m_shader->SetUniformMat4f("u_MVP", mvp);
			std::cout << "wsalt l 90" << "\n";
			Renderer.Draw(*m_VAO, *m_IndexBuffer, *m_shader);
		}
		{

			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_translationB);
			glm::mat4 mvp = m_proj * m_view * model;
			m_shader->SetUniformMat4f("u_MVP", mvp);
			Renderer.Draw(*m_VAO, *m_IndexBuffer, *m_shader);
		}
	}

	void TestTexture2D::OnImGuiRender()
	{
		ImGui::Text("This is a simple GUI");
		ImGui::SliderFloat3("translationA", &m_translationA.x, 0.0f, 960.0f);
		ImGui::SliderFloat3("translationB", &m_translationB.x, 0.0f, 960.0f);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}

}

