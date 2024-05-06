#include "sound.h"
#include <stdio.h>
#include <emscripten/emscripten.h>

EM_JS(void, play_audio, (char* audio_name), {
	const name = UTF8ToString(audio_name);
    const audio = preloadedAudios[name]?.cloneNode();
    if (!audio) return console.warn('unknown audio file', name);
    audio.currentTime = 0;
    audio.play();
});

void play_sound(SoundID id)
{
	char file_path[32];
	sprintf(file_path, "/res/sounds/%d.wav", id);

	play_audio(file_path);
}

int sounds_init()
{

	return 1;
}
