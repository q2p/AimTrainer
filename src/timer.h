#pragma once

#include <stdint.h>

uint64_t tick_number();
uint64_t ticks();
void timer_init();
void timing_loop();