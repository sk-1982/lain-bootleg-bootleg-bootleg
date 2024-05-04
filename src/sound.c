#include "sound.h"
#include <stdio.h>

void play_sound(SoundID id)
{
	char file_path[32];
	sprintf(file_path, "./res/sounds/%d.wav", id);
	
}

int sounds_init()
{


	return 1;
}
