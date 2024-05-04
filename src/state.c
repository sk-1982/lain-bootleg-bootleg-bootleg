#include "state.h"
#include "dressup.h"
#include "engine.h"
#include <stdint.h>
#include <emscripten/emscripten.h>

#include <stdio.h>

EM_JS(void, save_state, (int score, int theater_preview, int tool_state,
			 int outfit, int school_outfit_unlocked,
			 int cyberia_outfit_unlocked, int sweater_outfit_unlocked,
			 int bear_outfit_unlocked, int alien_outfit_unlocked,
			 int screwdriver_unlocked, int navi_unlocked), {
	  localStorage.setItem('lain-save', JSON.stringify({
	    score, theater_preview, tool_state, outfit, school_outfit_unlocked,
	    cyberia_outfit_unlocked, sweater_outfit_unlocked, bear_outfit_unlocked,
	    alien_outfit_unlocked, screwdriver_unlocked, navi_unlocked
	}))
      });

EM_JS(int, load_state, (int ptr), {
	const parse = v => {
		const val = +v;
		if (Number.isNaN(val))
			throw new Error(`Invalid value ${v}`);
		return val;
	};

	const state = localStorage.getItem('lain-save');
	if (!state)
		return 0;

	try {
		const payload = JSON.parse(state);
		['score', 'theater_preview', 'tool_state', 'outfit', 'school_outfit_unlocked',
		  'cyberia_outfit_unlocked', 'sweater_outfit_unlocked', 'bear_outfit_unlocked',
		  'alien_outfit_unlocked', 'screwdriver_unlocked', 'navi_unlocked'].forEach((k, i) => {
		       Module.setValue(ptr + i * 4, parse(payload[k]), 'i32');
		   });
		return 1;
	} catch (e) {
		console.error("failed to parse save:", e);
	}

	return 0;
});

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

int write_save_file(GameState* s)
{
	save_state(s->score, s->current_theater_preview, s->lain.tool_state,
		   s->lain.outfit, s->school_outfit_unlocked, s->cyberia_outfit_unlocked,
		   s->sweater_outfit_unlocked, s->bear_outfit_unlocked, s->alien_outfit_unlocked,
		   s->screwdriver_unlocked, s->navi_unlocked);

	return 1;
}

int load_save_file(Resources *resources, GameState *game_state)
{
	int32_t save_status[11];

	int res = load_state((int) save_status);
	if (!res) return 0;

	game_state->score = save_status[0];
	game_state->current_theater_preview = save_status[1];
	game_state->lain.tool_state = save_status[2];
	game_state->lain.outfit = save_status[3];
	game_state->school_outfit_unlocked = save_status[4];
	game_state->cyberia_outfit_unlocked = save_status[5];
	game_state->sweater_outfit_unlocked = save_status[6];
	game_state->bear_outfit_unlocked = save_status[7];
	game_state->alien_outfit_unlocked = save_status[8];
	game_state->screwdriver_unlocked = save_status[9];
	game_state->navi_unlocked = save_status[10];

	return 1;
}
