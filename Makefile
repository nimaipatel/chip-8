PKS=sdl2
CFLAGS=-Wall -ggdb -std=c11 -pedantic `pkg-config --cflags sdl2`
LIBS=`pkg-config --libs sdl2`

all: main.c
	$(CC) $(CFLAGS) -o chip-8 main.c $(LIBS)
