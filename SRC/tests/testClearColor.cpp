#include "testClearColor.h"
#include "../Renderer.h"
#include "../vendor/imgui/imgui.h"

namespace test {

	testClearColor::testClearColor()
		: ClearColor{0.0f,0.0f,0.0f,1.0f }
	{
		
	}

	testClearColor::~testClearColor()
	{

	}

	void testClearColor::OnUpdate(float DateTime)
	{
		
	}

	void testClearColor::OnRender()
	{
		glCall(glClearColor(ClearColor[0], ClearColor[1], ClearColor[2], ClearColor[3]));
		glCall(glClear(GL_COLOR_BUFFER_BIT));
	}

	void testClearColor::OnImGuiRender()
	{
		ImGui::ColorEdit4("Just clear Color", ClearColor);

	}

}