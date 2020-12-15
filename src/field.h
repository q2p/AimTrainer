#pragma once

#include <stdint.h>

typedef struct Pos {
	uint16_t x;
	uint16_t y;
} Pos;

typedef struct Target {
	Pos pos;
	uint16_t size;
} Target;

struct Field {
	Pos crosshair;
	Pos aspect;
	Target target_curr;
	Target target_next;
};

extern struct Field FIELD;

void drawbc();