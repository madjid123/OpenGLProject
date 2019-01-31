#pragma once
//define function that detect error in every Gl Function
#include<GL/glew.h>
#define ASSERT(x) if (!(x)) __debugbreak();
#define glCall(x) GlClearError();\
       x;\
       ASSERT(GlLogCall(#x,__FILE__,__LINE__))

void GlClearError();
bool GlLogCall(const char* function, const char* file, int line);