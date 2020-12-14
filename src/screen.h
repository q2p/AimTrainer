#pragma once

#include <stdint.h>
#include <SDL2/SDL.h>

extern uint16_t SCREEN_W;
extern uint16_t SCREEN_H;

extern uint8_t* SCREEN;

void render(SDL_Surface* surface);