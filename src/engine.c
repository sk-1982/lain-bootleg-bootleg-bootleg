#include <stdio.h>
#include <time.h>
#include <emscripten/emscripten.h>
#include <emscripten/html5.h>

#include "animations.h"
#include "cJSON.h"
#include "cvector.h"
#include "dressup.h"
#include "engine.h"
#include "kumashoot.h"
#include "menu.h"
#include "minigame.h"
#include "resources.h"
#include "scene.h"
#include "shader.h"
#include "sound.h"
#include "state.h"
#include "texture.h"
#include "theater.h"
#include "window.h"

#include "input.h"

extern void preload_video(void);

static int create_main_window(Engine* engine) {
	if (engine->main_window) return 1;
	// init main (menu) window
	if (!(make_window(&engine->main_window, COLLAPSED_MENU_WIDTH,
			  COLLAPSED_MENU_HEIGHT, "lain", NULL, false, engine))) {
		printf("Failed to create main window.\n");
		return 0;
	}

	// set user pointer to access engine inside callback function
	glfwSetWindowUserPointer(engine->main_window, engine);
	// set callbacks
	glfwSetMouseButtonCallback(engine->main_window, handle_menu_click);

	return 1;
}

int engine_init(Engine *engine)
{
	if (engine->initialized) return 1;

	preload_video();

	engine->resources.minigame.initialized = false;
	engine->resources.main.initialized = false;

    if (!create_main_window(engine))
		return 0;

	if (!init_resources(&engine->resources)) {
		printf("Failed to initialize resources.\n");
		return 0;
	};

	init_game_state(&engine->resources, &engine->game_state);

	init_menu(&engine->menu, &engine->game_state, &engine->resources);

	engine->minigame_window = NULL;
	engine->minigame.queued_minigame = NO_MINIGAME;
	engine->minigame.type = NO_MINIGAME;

	engine->initialized = 1;

	return 1;
}

static void engine_render(Engine *engine, double now)
{
	GLFWwindow *main_window = engine->main_window;
	Resources *resources = &engine->resources;
	Menu *menu = &engine->menu;
	GameState *game_state = &engine->game_state;

	GLFWwindow *minigame_window = engine->minigame_window;
	Minigame *minigame = &engine->minigame;

	glfwMakeContextCurrent(main_window);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	update_menu(menu, game_state, main_window, resources);

	draw_scene(&menu->scene, main_window, resources->main.shaders);

	if (minigame->type != NO_MINIGAME && can_refresh(now, minigame)) {
		glfwMakeContextCurrent(minigame_window);

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		update_minigame(resources, game_state, menu, &engine->minigame_window,
				minigame);

		if (minigame->type != NO_MINIGAME) {
			draw_minigame(resources, minigame_window, minigame);

			minigame->last_updated = now;
		}
	}

	if (minigame->type == NO_MINIGAME &&
	    minigame->queued_minigame != NO_MINIGAME) {
		start_queued_minigame(resources, game_state, menu, main_window,
				      &engine->minigame_window, minigame);
	}

	glfwPollEvents();

	game_state->time = now;
}

static void engine_renderloop(Engine *engine)
{
	while (!glfwWindowShouldClose(engine->main_window)) {
		engine_render(engine, glfwGetTime());
		emscripten_sleep(16);
	}
	if (engine->minigame.type != NO_MINIGAME)
	    destroy_minigame(engine->resources.main.textures, &engine->menu, &engine->minigame, &engine->minigame_window);
	glfwDestroyWindow(engine->main_window);
	engine->main_window = NULL;
	EM_ASM(Module.lainOnWindowClose(true));
}

void engine_run(Engine *engine)
{
	if (engine->running) return;

	engine->running = 1;

	collapse_menu(&engine->menu, &engine->resources);
	if (!create_main_window(engine))
		return;
	engine_renderloop(engine);

	engine->running = 0;

	if (!write_save_file(&engine->game_state)) {
		printf("Failed to write save file.\n");
	};
}
