#pragma once
#include<vector>
#include<functional>
namespace test {

	class test {
	public:
		test() {}
		virtual ~test() {}
		virtual void OnUpdate(float DateTime) {}
		virtual void OnRender() {}
		virtual void OnImGuiRender() {}
	};
	class testMenu: public test {
	public:
		testMenu(test*& currentTestPointer);
		void OnImGuiRender() override ;
		
		template<typename T>
		void RegisterTest(const std::string& name)
		{   
			std::cout << "Registering test " << name << std::endl;
			m_Tests.push_back(std::make_pair(name, []() {return new T(); }));
		}
	private:
		test*& m_CurrentTest ; 
		std::vector <std::pair<std::string, std::function<test*()>>> m_Tests;
	};
}