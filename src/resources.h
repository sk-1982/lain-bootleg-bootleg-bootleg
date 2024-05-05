#pragma once

#include "animations.h"
#include "cJSON.h"
#include "shader.h"
#include "sound.h"
#include "text.h"
#include <GLFW/glfw3.h>

typedef struct glresources {
	ShaderProgram shaders[MAX_SHADER_COUNT];
	Font fonts[MAX_FONT_COUNT];
	Texture textures[MAX_TEXTURE_COUNT];
	struct resources* resources;
	GLFWwindow* context;
	_Bool initialized;
} GLResources;

typedef struct resources {
	GLResources main;
	GLResources minigame;
	cJSON *animation_data;
	Animation animations[MAX_ANIMATION_COUNT];
	TheaterAnimation theater_animations[MAX_THEATER_ANIMATION_COUNT];
} Resources;

int init_resources(Resources *resources);
int init_glresources(GLResources* resources);
