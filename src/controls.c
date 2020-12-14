#include "controls.h"

void init_key(struct Key* key);
void clear_key(struct Key* key);

inline void init_key(struct Key* key) {
	key->held     = 0;
	key->pressed  = 0;
	key->released = 0;
}

inline void clear_key(struct Key* key) {
	key->pressed  = 0;
	key->released = 0;
}

inline void controls_init() {
	CONTROLS.is_pointer_locked = 0;

	CONTROLS.m_win_x = 0;
	CONTROLS.m_win_x = 0;
	CONTROLS.m_rel_x = 0;
	CONTROLS.m_rel_y = 0;

	init_key(&CONTROLS.lmb);
	init_key(&CONTROLS.rmb);
	init_key(&CONTROLS.w);
	init_key(&CONTROLS.a);
	init_key(&CONTROLS.s);
	init_key(&CONTROLS.d);
	init_key(&CONTROLS.esc);
	init_key(&CONTROLS.space);
}

inline void controls_clear_states() {
	CONTROLS.m_rel_x = 0;
	CONTROLS.m_rel_y = 0;
	clear_key(&CONTROLS.lmb);
	clear_key(&CONTROLS.rmb);
	clear_key(&CONTROLS.w);
	clear_key(&CONTROLS.a);
	clear_key(&CONTROLS.s);
	clear_key(&CONTROLS.d);
	clear_key(&CONTROLS.esc);
	clear_key(&CONTROLS.space);
}