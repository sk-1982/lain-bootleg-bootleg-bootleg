#pragma once

#include "menu.h"
#include "minigame.h"
#include "scene.h"
#include "state.h"
#include <GLFW/glfw3.h>

typedef struct engine Engine;

typedef struct engine {
	Resources resources;

	GLFWwindow *main_window;
	Menu menu;

	GLFWwindow *minigame_window;
	Minigame minigame;

	GameState game_state;
} Engine;


int engine_init(Engine *engine);
void engine_stop(Engine *engine);
void engine_run(Engine *engine);
