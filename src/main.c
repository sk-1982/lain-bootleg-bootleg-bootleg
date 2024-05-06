#include <stdio.h>
#include <emscripten/emscripten.h>
#include "engine.h"

static void error_callback(int error, const char *description)
{
	fprintf(stderr, "Code: %d\nError: %s\n", error, description);
}

static int init_glfw()
{
	static _Bool initialized = 0;

	if (initialized) return 1;

	if (!glfwInit()) {
		printf("Failed to initialize glfw.\n");
		return 0;
	}

	initialized = 1;

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwSetErrorCallback(error_callback);

	return 1;
}

Engine engine;

int main(void)
{
	if (!init_glfw()) {
		printf("Failed to initialize glfw\n");
		return -1;
	}

	if (!engine_init(&engine)) {
		printf("Failed to initialize engine. Exiting.\n");
		return -1;
	};

	engine_run(&engine);

	return 0;
}

EMSCRIPTEN_KEEPALIVE int close_main_window() {
	if (engine.main_window) {
		glfwSetWindowShouldClose(engine.main_window, GLFW_TRUE);
		return 1;
	}
	return 0;
}

EMSCRIPTEN_KEEPALIVE int close_minigame_window() {
	if (engine.minigame_window) {
		glfwSetWindowShouldClose(engine.minigame_window, GLFW_TRUE);
		return 1;
	}
	return 0;
}
