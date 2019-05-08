#pragma once
#include "test.h"
namespace test {
	
	class testClearColor : public test {
	public:
		testClearColor();
		~testClearColor();
		
		
		void OnUpdate(float DateTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		float ClearColor[4];

	};
}