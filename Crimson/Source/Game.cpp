#include "Game.h"

#include "Logger.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Crimson {
	void Game::Run(const char* windowTitle, std::pair<int, int> windowSize) {
		CR_ASSERT(glfwInit(), "%s\n", "Unable to initialise GLFW");

		m_window = glfwCreateWindow(windowSize.first, windowSize.second, windowTitle, NULL, NULL);
		CR_ASSERT(m_window != NULL, "%s\n", "Unable to create window");

		glfwMakeContextCurrent(m_window);

		CR_ASSERT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "%s\n", "Unable to initialise OpenGL");

		CR_LOG("%s\n", "Initialisation successful");

		while (!glfwWindowShouldClose(m_window)) {
			glClear(GL_COLOR_BUFFER_BIT);

			glfwSwapBuffers(m_window);

			glfwPollEvents();
		}

		glfwTerminate();
	}
}
