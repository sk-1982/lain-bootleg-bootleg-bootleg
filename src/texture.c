#include <stdio.h>
#include <stdlib.h>
#include <emscripten/emscripten.h>

#include "resources.h"
#include "sprite.h"
#include "texture.h"

static int init_texture(Texture *texture, TextureID texture_id)
{
	texture->id = texture_id;

	int width, height, nr_channels;

	char file_path[32];
	sprintf(file_path, "/res/sprites/%d.png", texture_id);
	char *data =
	    emscripten_get_preloaded_image_data(file_path, &width, &height);

	if (data == NULL) {
		printf("Failed to load texture.\n");
		return 0;
	}

	texture->size = (Vector2D){width, height};

	glGenTextures(1, &texture->gl_id);
	glBindTexture(GL_TEXTURE_2D, texture->gl_id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->size.x,
		     texture->size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	free(data);

	return 1;
}

Texture *texture_get(Resources *resources, int texture_id)
{
	Texture *texture = &resources->textures[texture_id];

	if (!texture->gl_id) {
		if (!init_texture(texture, texture_id)) {
			printf("Failed to initialize texture %d.\n",
			       texture_id);
			// TODO not sure what to do here
		};
	}

	return texture;
}

void textures_init(Resources *resources)
{
	for (int i = 0; i < MAX_TEXTURE_COUNT; i++) {
		resources->textures[i] = (Texture){0};
	};
}
