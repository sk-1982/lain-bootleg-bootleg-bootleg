#include "resources.h"
#include "sound.h"
#include "texture.h"

#include <stdio.h>
#include <string.h>

int init_resources(Resources *resources)
{
	load_textures(resources->embedded);

	textures_init(resources);

	if (!shaders_init(resources->shaders)) {
		printf("Failed to initialize shaders.\n");
		return 0;
	};

	fonts_init(resources);

	animations_init(resources);

	sounds_init(resources->sounds);

	return 1;
}
