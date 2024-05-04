#include "state.h"
#include "dressup.h"
#include "engine.h"

#include <stdio.h>

void reset_game_state(Resources *resources, GameState *game_state)
{
	game_state->score = 0;

	game_state->current_theater_preview = CLASSROOM_PREVIEW;

	game_state->lain = (Lain){.tool_state = NO_TOOLS};
	lain_set_outfit(resources, OUTFIT_DEFAULT, &game_state->lain);

	game_state->school_outfit_unlocked = false;
	game_state->alien_outfit_unlocked = false;
	game_state->bear_outfit_unlocked = false;
	game_state->sweater_outfit_unlocked = false;
	game_state->cyberia_outfit_unlocked = false;
	game_state->screwdriver_unlocked = false;
	game_state->navi_unlocked = false;
}

int init_game_state(Resources *resources, GameState *game_state)
{

	if (!load_save_file(resources, game_state)) {
		printf(
		    "Failed to load save file. Starting from a fresh state.\n");

		reset_game_state(resources, game_state);
	}

	return 1;
}

int write_save_file(Engine *engine)
{
	return 1;
}

int load_save_file(Resources *resources, GameState *game_state)
{
	return 0;
}
