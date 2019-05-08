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
		//position of the triangle 
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

		VertexArray va;
		VertexBuffer vb(position, 4 * 4 * sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);
		va.AddBuffer(vb, layout);
		IndexBuffer ib(indecies, 6);

		std::cout << glGetString(GL_VERSION) << std::endl;

		shader shader("res/shader/vbasic.shader");
		shader.Bind();
		Renderer Renderer;

		ImGui::CreateContext();
		ImGui_ImplGlfwGL3_Init(window, true);
		ImGui::StyleColorsDark();

		Texture texture("res/textures/h.png");
		texture.Bind();


		glm::mat4 proj = glm::ortho<float>(0.0, 960.0, 0.0, 540.0, -1.0, 1.0);
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));


		//shader.SetUniform4f("u_color", 0.1f, 0.5f, 0.8f, 1.0f);

		shader.SetUniformi("u_Texture", 0);

		va.Unbind();
		vb.unbind();
		ib.unbind();
		shader.Unbind();

		float r = 0.0f;
		float increment = 0.05f;

		glm::vec3 translationA(200.0f, 200.0f, 0.0f);
		glm::vec3 translationB(400.0f, 400.0f, 0.0f);
		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{

			/* Render here */
			Renderer.Clear();
			shader.Bind();
			ImGui_ImplGlfwGL3_NewFrame();
			{

				glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
				glm::mat4 mvp = proj * view * model;
				shader.SetUniformMat4f("u_MVP", mvp);
				Renderer.Draw(va, ib, shader);
			}
			{

				glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB);
				glm::mat4 mvp = proj * view * model;
				shader.SetUniformMat4f("u_MVP", mvp);
				Renderer.Draw(va, ib, shader);
			}

			//Make a simple animation with the color
			if (r > 1.0f)
				increment = -0.05f;
			else if (r < 0.0f)
				increment = 0.05f;
			r += increment;


			{
				ImGui::Text("This is a simple GUI");
				ImGui::SliderFloat3("translationA", &translationA.x, 0.0f, 960.0f);
				ImGui::SliderFloat3("translationB", &translationB.x, 0.0f, 960.0f);
				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			}

			ImGui::Render();
			ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}
	}
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	return 0;
}