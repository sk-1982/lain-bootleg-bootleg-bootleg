#include "resources.h"
#include "sound.h"
#include "texture.h"

#include <stdio.h>
#include <string.h>

int init_resources(Resources *resources)
{
	resources->minigame.resources = resources;
	resources->main.resources = resources;

	animations_init(resources);

	if (!sounds_init()) {
		return 0;
	};

	return 1;
}

int init_glresources(GLResources* resources) {
	if (resources->initialized) return 1;

	textures_init(resources);

	if (!shaders_init(resources->shaders)) {
		printf("Failed to initialize shaders.\n");
		return 0;
	}

	fonts_init(resources);

	resources->initialized = 1;

	return 1;
}
