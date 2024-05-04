#include "movie.h"
#include "window.h"

#include <stdio.h>
#include <string.h>

#define MOVIE_WIDTH 400
#define MOVIE_HEIGHT 300

static void init_movie_buffers(Movie *movie)
{
	glGenVertexArrays(1, &movie->VAO);
	glBindVertexArray(movie->VAO);

	glGenBuffers(1, &movie->VBO);
	glBindBuffer(GL_ARRAY_BUFFER, movie->VBO);

	float left_x = -0.75f;
	float right_x = 0.75f;

	float top_y = -0.75;
	float bottom_y = 0.75;

	// clang-format off
	float movie_quad_vertices[] = {
	    left_x,  bottom_y,  0.0f, 1.0f,
	    left_x, top_y,  0.0f, 0.0f,
	    right_x, top_y,  1.0f, 0.0f,

	    left_x,  bottom_y,  0.0f, 1.0f,
	    right_x, top_y,  1.0f, 0.0f,
	    right_x,  bottom_y,  1.0f, 1.0f
	};
	// clang-format on

	glBufferData(GL_ARRAY_BUFFER, sizeof(movie_quad_vertices),
		     movie_quad_vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float),
			      (void *)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float),
			      (void *)(2 * sizeof(float)));

	glGenFramebuffers(1, &movie->FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, movie->FBO);

	glGenTextures(1, &movie->texture_buffer);
	glBindTexture(GL_TEXTURE_2D, movie->texture_buffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, MINIGAME_WIDTH, MINIGAME_HEIGHT,
		     0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, 0);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
			       GL_TEXTURE_2D, movie->texture_buffer, 0);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

int movie_init(Movie *movie)
{
	init_movie_buffers(movie);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) !=
	    GL_FRAMEBUFFER_COMPLETE) {
		printf("Framebuffer is incomplete.\n");
		return 0;
	}

	return 1;
}

_Bool movie_render(ShaderProgram shader, Movie *movie)
{
	glBindFramebuffer(GL_FRAMEBUFFER, movie->FBO);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(shader);

	glBindVertexArray(movie->VAO);
	glBindTexture(GL_TEXTURE_2D, movie->texture_buffer);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	return true;
}

void movie_free(Movie *movie)
{
	
}
