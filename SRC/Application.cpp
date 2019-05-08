#include <GL/glew.h> 
#include <GLFW/glfw3.h>

#include<iostream>
#include<fstream>
#include<string>
#include<sstream>

#include"Renderer.h"

#include "VertexBuffer.h"
#include"IndexBuffer.h"
#include "VertexBufferLayout.h"
#include"VertexArray.h"

#include "Shader.h"

#include "Texture.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include"imgui/imgui.h"
#include"imgui/imgui_impl_glfw_gl3.h"
#include "tests/testClearColor.h"
#include "tests/TestTexture2D.h"

int main(void)
{
	glewInit();
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	// Frame controller
	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)
		std::cout << "Error!!" << std::endl;
	{
		glCall(glEnable(GL_BLEND));
		glCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		std::cout << glGetString(GL_VERSION) << std::endl;

		Renderer render;

		ImGui::CreateContext();
		ImGui_ImplGlfwGL3_Init(window, true);
		ImGui::StyleColorsDark();
		
		test::test *CurrentTest = nullptr;
		test::testMenu *testMenu = new test::testMenu(CurrentTest);
		CurrentTest = testMenu;
		testMenu->RegisterTest<test::testClearColor>("Clear color");
		testMenu->RegisterTest<test::TestTexture2D>("2D Texture");

	
		while (!glfwWindowShouldClose(window))
		{
			glCall(glClearColor(0.5f, 0.0f, 0.0f, 1.0f));
			render.Clear();
			ImGui_ImplGlfwGL3_NewFrame();

			if (CurrentTest)
			{
				CurrentTest->OnUpdate(0.0f);
				CurrentTest->OnRender();
				ImGui::Begin("test");
				if (CurrentTest != testMenu && ImGui::Button("<-"))
				{
					delete CurrentTest;
					CurrentTest = testMenu;
				}
				CurrentTest->OnImGuiRender();
				ImGui::End();
			}
			ImGui::Render();
			ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}
	
		
		if (CurrentTest != testMenu)
		{
			delete CurrentTest;
			delete testMenu;
		}
		delete CurrentTest;
	}
	
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	return 0;
}