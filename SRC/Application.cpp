#include<GL/glew.h> //rani habas fi ERRORS glGetError()
#include <GLFW/glfw3.h>

#include<iostream>
#include<fstream>
#include<string>
#include<sstream>

#include"rendrer.h"

#include "VertexBuffer.h"
#include"IndexBuffer.h"

#include"VertexArray.h"

#include "Shader.h"


int main(void)
{
	glewInit();
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	
	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	
	//Speed of the frames
	glfwSwapInterval(1);
	
	if (glewInit() != GLEW_OK)
		std::cout << "Error!!" << std::endl;
	{

		//positions of the triangle 
		float position[] = {
		   -0.5f, -0.5f, //0
			0.5f, -0.5f, //1
			0.5f,  0.5f, //2
		   -0.5f,  0.5f  //3
		};

		//repeated indecies of the square (optimized method)
		unsigned int indecies[] =
		{ 0,1,2,
		  2,3,0
		};

		/*unsigned int vao;
		glCall(glGenVertexArrays(1, &vao));
		glCall(glBindVertexArray(vao));*/

		VertexArray va;
		VertexBuffer vb(position, 4 * 2 * sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(2);
		va.AddBuffer(vb, layout);
		IndexBuffer ib(indecies, 6);

		std::cout << glGetString(GL_VERSION) << std::endl;

		shader shader("res/shader/vbasic.shader");
		shader.Bind();
		
		shader.SetUniform4("u_color", 0.1f, 0.5f, 0.8f, 1.0f);
		// Create a shader (import GLSL source code and compile it)
	
		

		
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
			glClear(GL_COLOR_BUFFER_BIT);
			glColor3f(0.0, 0.5, 0.0);

			shader.Bind();
			shader.SetUniform4("u_color", r, 0.5f, 0.8f, 1.0f);

			va.Bind();
			ib.Bind();


			//Make a simple animation with the color
			if (r > 1.0f)
				increment = -0.05f;
			else if (r < 0.0f)
				increment = 0.05f;
			r += increment;

			glCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));


			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}

	}
	glfwTerminate();
	return 0;
}
