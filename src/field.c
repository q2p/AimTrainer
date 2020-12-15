#include "field.h"
#include "screen.h"
#include "timer.h"
#include <SDL2/SDL.h>

struct Field FIELD;

uint16_t bezier_point(uint8_t t128, uint16_t start, uint16_t control, uint16_t end) {
	uint8_t t0 =       t128;
	uint8_t t1 = 128 - t128;
	uint32_t a =     (uint32_t) start   * t1 * t1;
	uint32_t b = 2 * (uint32_t) control * t1 * t0;
	uint32_t c =     (uint32_t) end     * t0 * t0;
	uint32_t r = a + b + c;
	r >>= 14;
	return r;
}

void init_field() {
	FIELD.aspect.x = 2;
	FIELD.aspect.y = 1;
	FIELD.crosshair.x = UINT16_MAX / 2;
	FIELD.crosshair.y = UINT16_MAX / 2;
	FIELD.target_curr.pos.x = 0;
	FIELD.target_curr.pos.y = 0;
	FIELD.target_next.pos.x = 0;
	FIELD.target_next.pos.y = 0;
}

void render_square(Pos pos, uint16_t size) {
	// TODO: в коде есть недочёты которые могут привести к выходу за пределы массива.
	// TODO: я старался оптимизировать код под линейность записи, но это привело к плохой читаемости
	int32_t x0 = (int32_t) pos.x - (int32_t) size;
	int32_t x1 = (int32_t) pos.x + (int32_t) size;
	int32_t y0 = (int32_t) pos.y - (int32_t) size;
	int32_t y1 = (int32_t) pos.y + (int32_t) size;

	uint16_t xs;
	if (x0 < 0) {
		xs = 0;
	} else {
		xs = x0;
	}
	uint16_t xe;
	if (x1 >= SCREEN_W) {
		xe = SCREEN_W;
	} else {
		xe = x1+1;
	}

	uint16_t ys;
	if (y0 < 1) {
		ys = 0;
	} else {
		ys = y0 + 1;
	}
	uint16_t ye;
	if (y1 > SCREEN_H) {
		ye = SCREEN_H;
	} else {
		ye = y1;
	}
	if (y0 >= 0 && y0 < SCREEN_H) {
		uint32_t offset = y0 * SCREEN_W;
		for(uint16_t x = xs; x != xe; x++) {
			SCREEN[offset + x] = 255;
		}
	}
	for(uint16_t y = ys; y != ye; y++) {
		uint32_t offset = y * SCREEN_W;
		if (x0 >= 0 && x0 < SCREEN_H) {
			SCREEN[offset + x0] = 255;
		}
		uint16_t x = xs + 1;
		if (y & 1) {
			x = x + 1 - (x & 1);
		} else {
			x = x + 0 + (x & 1);
		}
		for(; x < xe; x += 2) {
			SCREEN[offset + x] = 0;
		}
		if (x1 >= 0 && x1 < SCREEN_H) {
			SCREEN[offset + x1] = 255;
		}
	}
	if (y1 >= 0 && y1 < SCREEN_H) {
		uint32_t offset = y1 * SCREEN_W;
		for(int32_t x = xs; x != xe; x++) {
			SCREEN[offset + x] = 255;
		}
	}
}

void drawbc() {
	Pos a = {            2,            2 };
	Pos c = { SCREEN_W - 2, SCREEN_H / 2 };
	Pos b = {            2, SCREEN_H - 2 };

	for(uint8_t t = 0; t <= 128; t++) {
		Pos p;
		p.x = bezier_point(t, a.x, c.x, b.x);
		p.y = bezier_point(t, a.y, c.y, b.y);
		SCREEN[p.y * SCREEN_W + p.x] = 255;
		if ((tick_number() >> 3) % 129 == t) {
			render_square(p, 16);
		}
	}
	SCREEN[c.y * SCREEN_W + c.x] = 255;
}