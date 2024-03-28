#include "input.h"

bool input::isMouseActive = false;
int input::pressedKey = 0;
float input::xyCusorPos[2] = { 0, 0 };
float input::lastXYCusorPos[2] = { 0, 0 };
int input::pressedMouseButton = 0;

float lastX = 1280.0f / 2.0f;
float lastY = 720.0f / 2.0f;
bool firstMouse = true;


input::input(GLFWwindow* window)
	:window(window)
{
}

void input::Initialize_()
{
	glfwSetKeyCallback(window, (GLFWkeyfun)[](GLFWwindow* window, int key, int scancode, int action, int mods) {
		if (action == GLFW_PRESS || action == GLFW_REPEAT) {
			input::pressedKey = key;
		}
		});

	glfwSetCursorPosCallback(window, (GLFWcursorposfun)[](GLFWwindow* window, double xpos, double ypos)
		{
			if (firstMouse)
			{
				lastX = xpos;
				lastY = ypos;
				firstMouse = false;
			}

			float xoffset = xpos - lastX;
			float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

			lastX = xpos;
			lastY = ypos;

			input::xyCusorPos[0] = xoffset;
			input::xyCusorPos[1] = yoffset;

			/*float L = 0, B = 0; auto[R, T] = Application::GetWidthAndHieght();

			//input::xyCusorPos[0] = ((2/r-l) * (float)xpos) - (r + l / r - l);//converting from screen coordinates to NDC space
			//input::xyCusorPos[1] = (((2/t-b) * (float)yPos) - (t + b / t - b)); //using -1 to change sign of y value because the return cusor position has an origin

			float a = (float)((float)xpos * 2.0f / R) - 1.0f;
			float b = -1.0f * ((float)((float)yPos * 2.0f / T) - 1.0f);		//of [0, -1] in NDC that is the top left corner

			if (a >= 0.9765f)
			{
				input::xyCusorPos[0] = glm::round(a);
			}
			else if (a <= -0.9765f)
			{
				input::xyCusorPos[0] = glm::round(a);
			}
			else
			{
				input::xyCusorPos[0] = a;
			}

			if (b >= 0.9565f)
			{
				input::xyCusorPos[1] = glm::round(b);
			}

			else if (b <= -0.9565f)
			{
				input::xyCusorPos[1] = glm::round(b);
			}

			else
			{
				input::xyCusorPos[1] = b;
			}*/
		});

}

bool input::is_mouse_moving()
{
	if (input::lastXYCusorPos[0] != input::xyCusorPos[0])
	{
		input::lastXYCusorPos[0] = input::xyCusorPos[0];
		input::lastXYCusorPos[1] = input::xyCusorPos[1];

		return true;
	}
	else
	{
		return false;
	}
}

bool input::is_Key_active(int key)
{
	if (key == pressedKey)
	{
		pressedKey = GL_ZERO;
		return true;
	}
	return false;
}



float const * input::Return_Curso_info()
{
	return xyCusorPos;
}
