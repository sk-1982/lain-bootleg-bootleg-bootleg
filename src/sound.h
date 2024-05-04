#pragma once

typedef enum {
	SND_110,
	SND_111,
	SND_112,
	SND_113,
	SND_114,
	SND_115,
	SND_116,
	SND_117,
	SND_118,
	SND_119,
	SND_120,
} SoundID;

void play_sound(SoundID id);
int sounds_init();
