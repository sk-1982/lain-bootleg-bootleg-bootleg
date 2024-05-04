#pragma once

#include <GL/glew.h>

#include "shader.h"

typedef struct {
	GLuint texture_buffer;
	GLuint FBO;
	GLuint VBO;
	GLuint VAO;
} Movie;

int movie_init(Movie *movie);
_Bool movie_render(ShaderProgram shader, Movie *movie);
void movie_free(Movie *movie);
