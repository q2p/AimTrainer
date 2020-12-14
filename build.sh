#/bin/sh
gcc src/main.c src/timer.c src/controls.c src/screen.c  src/prng.c -w -lSDL2 -O3 --release && ./a.out