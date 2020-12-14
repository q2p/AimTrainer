#include "prng.h"

uint64_t x, w, s;

inline rand_seed(uint64_t seed) {
	x = 0;
	w = 0;
	s = (seed << 1) + 0xb5ad4eceda1ce2a9;
	rand_32();
}

uint32_t rand_32() {
	x *= x;
	w += s;
	x += w;
	x = (x>>32) | (x<<32);
	return x;
}