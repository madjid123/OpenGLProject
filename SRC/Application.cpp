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
		   -0.5f, -0.5f, 0.0f, 0.0f, //0
			0.5f, -0.5f, 1.0f, 0.0f, //1
			0.5f,  0.5f, 1.0f, 1.0f, //2
		   -0.5f,  0.5f, 0.0f, 1.0f  //3
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
		Texture texture("res/textures/h.png");
		texture.Bind();


		glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);
		shader.SetUniform4f("u_color", 0.1f, 0.5f, 0.8f, 1.0f);
		shader.SetUniformMat4f("u_MVP", proj);

		shader.SetUniformi("u_Texture", 0);

		va.Unbind();
		vb.unbind();
		ib.unbind();
		shader.Unbind();

		float r = 0.0f;
		float increment = 0.05f;

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{

			/* Render here */
			Renderer.Clear();
			shader.Bind();
			shader.SetUniform4f("u_color", r, 0.5f, 0.8f, 1.0f);
			Renderer.Draw(va, ib, shader);

			//Make a simple animation with the color
			if (r > 1.0f)
				increment = -0.05f;
			else if (r < 0.0f)
				increment = 0.05f;
			r += increment;

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}
	}
	glfwTerminate();
	return 0;
}