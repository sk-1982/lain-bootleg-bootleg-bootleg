#include "sound.h"
#include <stdio.h>
#include <SDL.h>
#include <SDL_mixer.h>


void play_sound(SoundID id)
{
	char file_path[32];
	sprintf(file_path, "/res/sounds/%d.wav", id);
	Mix_Chunk* chunk = Mix_LoadWAV(file_path);
	if (!chunk) {
		printf("Failed to load audio %d\n", id);
		return;
	}

	Mix_PlayChannel(-1, chunk, 0);
	Mix_FreeChunk(chunk);
}

int sounds_init()
{
	if(SDL_Init(SDL_INIT_AUDIO) < 0) {
		printf("Failed to initialize SDL\n");
		return 0;
	}

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 1, 1024) < 0) {
		printf("Failed to initialize audio\n");
		return 0;
	}

	return 1;
}
