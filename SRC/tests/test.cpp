#include"test.h"
#include "imgui/imgui.h"

namespace test {
	testMenu::testMenu(test*& currentTestPointer)
		: m_CurrentTest(currentTestPointer)
	{}
	void testMenu::OnImGuiRender()
	{
		for (auto& test : m_Tests)
		{
			if (ImGui::Button(test.first.c_str()))
				m_CurrentTest = test.second();
		}
	}
}