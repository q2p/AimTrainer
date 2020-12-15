#include "screen.h"
#include "prng.h"

uint16_t SCREEN_W = 4*160;
uint16_t SCREEN_H = 4*90;

uint8_t* SCREEN;

uint32_t min_u32(uint32_t a, uint32_t b);
uint32_t clamp_u32(uint32_t x, uint32_t min, uint32_t max);

inline uint32_t min_u32(uint32_t a, uint32_t b) {
	if (a < b)
		return a;
	else
		return b;
}

inline uint32_t clamp_u32(uint32_t x, uint32_t min, uint32_t max) {
	if (x < min)
		return min;

	if (x > max)
		return max;

	return x;
}

inline void render(SDL_Surface* surface) {
	if (SCREEN_W != surface->w || SCREEN_H != surface->h) {
		return;
	}
	
	SDL_LockSurface(surface);

	uint8_t l = surface->format->BytesPerPixel;
	uint32_t c[256];
	for(uint16_t i = 255; i != 0; i--) {
		c[i] = SDL_MapRGB(surface->format, 255, 255, 255);
	}
	c[0] = SDL_MapRGB(surface->format, 0, 0, 0);

	uint8_t* sc_end = SCREEN + SCREEN_W * SCREEN_H;
	uint8_t* sc = SCREEN;
	uint8_t* sr = surface->pixels;
	while (sc != sc_end) {
		*(uint32_t*)sr = c[*sc];
		sc++;
		sr += l;
	}
	memset(SCREEN, 0, (size_t) SCREEN_W * (size_t) SCREEN_H);
	SDL_UnlockSurface(surface);
}