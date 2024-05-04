#include <stdio.h>
#include <stdlib.h>
#include <emscripten/emscripten.h>
#include <contrib.glfw3/GLFW/emscripten_glfw3.h>

#include "menu.h"
#include "scene.h"
#include "window.h"

int make_window(GLFWwindow **window, int width, int height, char *name,
		GLFWwindow *shared_ctx, _Bool centered)
{
	if (shared_ctx)
		emscripten_glfw_set_next_window_canvas_selector("#canvas2");

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

	*window = glfwCreateWindow(width, height, name, NULL, shared_ctx);
	if (window == NULL) {
		printf("Failed to initialize window.\n");
		glfwTerminate();
		return 0;
	}

	glfwShowWindow(*window);

	glfwMakeContextCurrent(*window);
	EM_ASM(GL.currentContext.version = 2);

	// enable alpha support
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if (glewInit() != GLEW_OK) {
		printf("Failed to initialize glew.\n");
		glfwTerminate();
		return 0;
	}

	glEnable(GL_DEBUG_OUTPUT);

	if (shared_ctx != NULL) {
		Engine *engine = (Engine *)glfwGetWindowUserPointer(shared_ctx);
		glfwSetWindowUserPointer(*window, engine);
		glfwSetMouseButtonCallback(*window, handle_minigame_event);
	}
	return 1;
}
