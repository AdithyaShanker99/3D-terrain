#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

#define Error_check(x) glcheckerrors();\
x;\
glLogCall(#x, __FILE__, __LINE__)

#include "GLAD/include/glad/glad.h"
#include "GLFW/glfw3.h"


void glLogCall(const char* Function, const char* file, unsigned int line);
void glcheckerrors();



#endif //
