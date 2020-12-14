#pragma once

#include <stdint.h>

void controls_init();
void controls_clear_states();

struct Key {
	uint8_t held;
	uint8_t pressed;
	uint8_t released;
};

struct Controls {
	uint8_t is_pointer_locked;
	int32_t m_win_x;
	int32_t m_win_y;
	int32_t m_rel_x;
	int32_t m_rel_y;
	struct Key lmb;
	struct Key rmb;
	struct Key w;
	struct Key a;
	struct Key s;
	struct Key d;
	struct Key esc;
	struct Key space;
} CONTROLS;