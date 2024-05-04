#pragma once

#include "animations.h"
#include "cJSON.h"
#include "shader.h"
#include "sound.h"
#include "text.h"

typedef struct resources {
	ShaderProgram shaders[MAX_SHADER_COUNT];
	Font fonts[MAX_FONT_COUNT];
	Texture textures[MAX_TEXTURE_COUNT];
	cJSON *animation_data;
	Animation animations[MAX_ANIMATION_COUNT];
	TheaterAnimation theater_animations[MAX_THEATER_ANIMATION_COUNT];
} Resources;

int init_resources(Resources *resources);
