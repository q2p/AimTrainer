#/bin/sh
gcc \
src/main.c \
src/timer.c \
src/controls.c \
src/screen.c \
src/prng.c \
src/field.c \
-w -lSDL2 \
-O3 --release \
-s \
-march=native \
&& \
./a.out
