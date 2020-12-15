#include <SDL2/SDL.h>
#include <stdlib.h>
#include "timer.h"
#include "controls.h"
#include "screen.h"
#include "field.h"

int main() {
	controls_init();
	rand_seed(0);

	if(SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
		return 1;
	}
	
	SDL_Window* window = SDL_CreateWindow(
		"AimTrainer",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_W, SCREEN_H,
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
	);
	
	if (window == NULL) {
		return 1;
	}

	SDL_Surface* screenSurface = SDL_GetWindowSurface( window );

	SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );
	
	SDL_UpdateWindowSurface( window );

	uint32_t windowID = SDL_GetWindowID(window);

	SCREEN = (uint8_t*) malloc(SCREEN_W * SCREEN_H);
	if (SCREEN == NULL) {
		return 1;
	}
	SDL_DisplayMode dm;
	if (SDL_GetDesktopDisplayMode(0, &dm) != 0) {
		return 1;
	}
	if (SDL_SetWindowDisplayMode(window, &dm) != 0) {
		return 1;
	}
	if (SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN) != 0) {
		return 1;
	}

	SDL_Event event;
	timer_init();
	uint8_t update_surface = 1;
	uint8_t quit = 0;
	uint64_t offset = tick_number();
	while(1) {
		SDL_Log("%d %d", ticks(), tick_number()-offset);
		while(SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				quit = 1;
				break;
			} else if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
				uint8_t held = event.type == SDL_KEYDOWN;
				if (event.key.windowID != windowID) {
					continue;
				}
				SDL_Scancode code = event.key.keysym.scancode;
				struct Key* key;
				if(code == SDL_SCANCODE_ESCAPE) {
					key = &CONTROLS.esc;
				} else if(code == SDL_SCANCODE_SPACE) {
					key = &CONTROLS.space;
				} else if(code == SDL_SCANCODE_W) {
					key = &CONTROLS.w;
				} else if(code == SDL_SCANCODE_A) {
					key = &CONTROLS.a;
				} else if(code == SDL_SCANCODE_S) {
					key = &CONTROLS.s;
				} else if(code == SDL_SCANCODE_D) {
					key = &CONTROLS.d;
				} else {
					continue;
				}
				if (held) {
					key->held = 1;
					key->pressed = 1;
				} else {
					key->held = 0;
					key->released = 1;
				}
			} else if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) {
				uint8_t held = event.type == SDL_MOUSEBUTTONDOWN;
				if (event.button.windowID != windowID) {
					continue;
				}
				uint8_t code = event.button.button;
				struct Key* key;
				if(code == SDL_BUTTON_LEFT) {
					key = &CONTROLS.lmb;
				} else if(code == SDL_BUTTON_RIGHT) {
					key = &CONTROLS.rmb;
				} else {
					continue;
				}
				if (held) {
					key->held = 1;
					key->pressed = 1;
				} else {
					key->held = 0;
					key->released = 1;
				}
			} else if (event.type == SDL_MOUSEMOTION) {
				if (event.motion.windowID != windowID) {
					continue;
				}
				CONTROLS.m_win_x = event.motion.x;
				CONTROLS.m_win_y = event.motion.y;
				CONTROLS.m_rel_x += event.motion.xrel;
				CONTROLS.m_rel_y += event.motion.yrel;
			} else if (event.type == SDL_WINDOWEVENT) {
				if (event.window.windowID != windowID) {
					continue;
				}
				switch (event.window.event) {
					case SDL_WINDOWEVENT_SHOWN:
						break;
					case SDL_WINDOWEVENT_HIDDEN:
						break;
					case SDL_WINDOWEVENT_EXPOSED:
						break;
					case SDL_WINDOWEVENT_MOVED:
						break;
					case SDL_WINDOWEVENT_RESIZED:
					case SDL_WINDOWEVENT_SIZE_CHANGED:
							update_surface = 1;
							update_surface = 1;
							break;
					case SDL_WINDOWEVENT_MINIMIZED:
							break;
					case SDL_WINDOWEVENT_MAXIMIZED:
							break;
					case SDL_WINDOWEVENT_RESTORED:
							break;
					case SDL_WINDOWEVENT_ENTER:
							break;
					case SDL_WINDOWEVENT_LEAVE:
							break;
					case SDL_WINDOWEVENT_FOCUS_GAINED:
							break;
					case SDL_WINDOWEVENT_FOCUS_LOST:
							break;
					case SDL_WINDOWEVENT_CLOSE:
							quit = 1;
							break;
					case SDL_WINDOWEVENT_TAKE_FOCUS:
							break;
					case SDL_WINDOWEVENT_HIT_TEST:
							break;
					default:
							break;
				}
			}
		}
		if (quit || CONTROLS.esc.pressed) {
			break;
		}

		if(update_surface) {
			update_surface = 0;
			screenSurface = SDL_GetWindowSurface(window);
			if (SCREEN_W != screenSurface->w || SCREEN_H != screenSurface->h) {
				SCREEN_W = screenSurface->w;
				SCREEN_H = screenSurface->h;
				if (SCREEN_W == 0) {
					SCREEN_W = 1;
				}
				if (SCREEN_H == 0) {
					SCREEN_H = 1;
				}
				SCREEN = (uint8_t*) realloc(SCREEN, SCREEN_W * SCREEN_H);
				if (SCREEN == NULL) {
					return 1;
				}
			}
		}

		timing_loop();

		drawbc();

		render(screenSurface);

		SDL_UpdateWindowSurface(window);

		controls_clear_states();
	}

	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}