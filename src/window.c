#include <stdio.h>
#include <stdlib.h>
#include <emscripten/emscripten.h>
#include <contrib.glfw3/GLFW/emscripten_glfw3.h>

#include "menu.h"
#include "scene.h"
#include "window.h"

EM_JS(char*, get_main_window_selector, (), {
	return stringToNewUTF8(Module.lainMainWindowSelector);
});

EM_JS(char*, get_minigame_window_selector, (), {
	return stringToNewUTF8(Module.lainMinigameWindowSelector);
});

int make_window(GLFWwindow **window, int width, int height, char *name,
		GLFWwindow *shared_ctx, _Bool centered, Engine* engine)
{
	int res;

	if (!engine)
		engine = glfwGetWindowUserPointer(shared_ctx);

	char* selector = shared_ctx ? get_minigame_window_selector() : get_main_window_selector();
	emscripten_glfw_set_next_window_canvas_selector(selector);
	free(selector);

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

	*window = glfwCreateWindow(width, height, NULL, NULL, shared_ctx);
	if (window == NULL) {
		printf("Failed to initialize window.\n");
		glfwTerminate();
		return 0;
	}

	GLResources* resources = shared_ctx ? &engine->resources.minigame : &engine->resources.main;
	resources->context = *window;

	glfwShowWindow(*window);

	EM_ASM({
	    Module.lainOnWindowOpen(!!$0, UTF8ToString($1));
    }, !shared_ctx, name);

	glfwMakeContextCurrent(*window);
	EM_ASM(GL.currentContext.version = 2);

	res = init_glresources(resources);
	if (!res) {
		printf("Failed to initialize gl resources.\n");
		return 0;
	}

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
		glfwSetWindowUserPointer(*window, engine);
		glfwSetMouseButtonCallback(*window, handle_minigame_event);
	}
	return 1;
}
