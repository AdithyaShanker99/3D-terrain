#pragma once
#include "error.h"

class input
{
public:
	input() = default;
	input(GLFWwindow* window);
	~input() = default;

	bool is_mouse_moving();

	bool is_Key_active(int key);


	float const * Return_Curso_info();

	void Initialize_();

	public:
	GLFWwindow* window;
	static bool isMouseActive;
	static int pressedKey;
	static int pressedMouseButton;
	static float xyCusorPos[2];
	static float lastXYCusorPos[2];
};


