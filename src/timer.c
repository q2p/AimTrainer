#include "timer.h"

#include <SDL2/SDL.h>

const uint16_t TARGET_FPS = 250;

uint64_t current_tick_value;
uint64_t delta_value;

uint64_t last_tick;
uint64_t freq;

inline void timer_init() {
	freq = SDL_GetPerformanceFrequency();
	last_tick = SDL_GetPerformanceCounter() * TARGET_FPS / freq;
	current_tick_value = last_tick;
}

inline uint64_t tick_number() {
	return current_tick_value;
}
inline uint64_t ticks() {
	return delta_value;
}

inline void timing_loop() {
	while(1) {
		uint64_t time_stamp = SDL_GetPerformanceCounter();

		current_tick_value = time_stamp * TARGET_FPS / freq;

		if (current_tick_value > last_tick) {
			break;
		}

		uint64_t to_sleep = ((last_tick + 1) - current_tick_value) * 1000 / TARGET_FPS;
		if (to_sleep == 0) {
			to_sleep = 1;
		}
		SDL_Delay(to_sleep);
	}

	delta_value = current_tick_value - last_tick;

	last_tick = current_tick_value;
}