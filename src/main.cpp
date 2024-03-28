

#include "error.h"

#include <iostream>

#include "application/Camera.h"

#include "buffers.h"

#include "application/input.h"

#include "application/terrain/Terrain_manager.h"


int main()
{
	//
	system("color 1");

	if (!glfwInit()) {
		std::cout << "initialization failed!" << std::endl;
		return 0;
	}
	//................................................................................
	GLFWwindow* m_window = glfwCreateWindow(1280, 720, "3D Terrain", nullptr, nullptr);

	int max, min, r;
	glfwGetVersion(&max, &min, &r);
	//..............................................................................
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, max);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, min);
	//...............................................................
	glfwMakeContextCurrent(m_window);

	if (!(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)))
	{
		std::cout << "error" << std::endl;
	}

	glfwSetErrorCallback((GLFWerrorfun)[](int error_code, const char* description) {
		fprintf(stderr, "Error: %s\n", description);
		}); 

	input Event_Handler = input(m_window);
	Event_Handler.Initialize_();

	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	CameraController FreeLookCamera = CameraController();
	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 5.0f));

	float height_scale_ = 90.0f;

	HeightMap map = HeightMap("textures/Default.png", height_scale_);

	Error_check(glEnable(GL_DEPTH_TEST));
	Error_check(glDepthFunc(GL_LEQUAL));

	float lastFrame = 0;
	float currentFrame;
	float deltaTime;

	glm::vec3 lightPos = glm::vec3(0.0f, 10.0f, 0.0f);

	while (!glfwWindowShouldClose(m_window))
	{
		Error_check(glClearColor(0.0f, 0.75f, 0.80f, 1.0f));
		{
			Error_check(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

			glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -4.0f, 0.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(20.0f, 20.0f, 20.0f));
			glm::mat4 cubemodel = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.5f, 0.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f / 2.5f, 1.0f / 2.5f, 1.0f / 2.5f));


				currentFrame = glfwGetTime();
				deltaTime = currentFrame - lastFrame;
				lastFrame = currentFrame;

				float ts = lastFrame;

				float g = 0.025f;
				if (Event_Handler.is_Key_active(GLFW_KEY_A))
				{
					FreeLookCamera.ProcessKeyboard(Camera_Movement::LEFT, ts * g);
				}
				else if (Event_Handler.is_Key_active(GLFW_KEY_D))
				{
					FreeLookCamera.ProcessKeyboard(Camera_Movement::RIGHT, ts * g);
				}

				else if (Event_Handler.is_Key_active(GLFW_KEY_W))
				{
					FreeLookCamera.ProcessKeyboard(Camera_Movement::FORWARD, ts * g);
				}

				else if (Event_Handler.is_Key_active(GLFW_KEY_S))
				{
					FreeLookCamera.ProcessKeyboard(Camera_Movement::BACKWARD, ts * g);
				}

				else if (Event_Handler.is_Key_active(GLFW_KEY_UP))
				{
					lightPos.y += 0.5f;
				}

				else if (Event_Handler.is_Key_active(GLFW_KEY_DOWN))
				{
					lightPos.y -= 0.5f;
				}

				else if (Event_Handler.is_Key_active(GLFW_KEY_RIGHT))
				{
					lightPos.x += 0.5f;
				}

				else if (Event_Handler.is_Key_active(GLFW_KEY_LEFT))
				{
					lightPos.x -= 0.5f;
				}

				if (Event_Handler.is_mouse_moving())
				{
					FreeLookCamera.ProcessMouseMovement(Event_Handler.Return_Curso_info()[0], Event_Handler.Return_Curso_info()[1]);
				}
			

				map.BindVao();

				map.Render(model,
					FreeLookCamera.GetViewMatrix(),
					glm::perspective(glm::radians(45.0f), (float)1280 / (float)720, 0.1f, 100.0f), FreeLookCamera.Position, lightPos);
		
		}

		glfwSwapBuffers(m_window);

		glfwPollEvents();
	}

	glfwTerminate();
	system("pause");
	return 0;
    return 0;
} 

