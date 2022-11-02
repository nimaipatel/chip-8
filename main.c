#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#define WINDOW_TITLE "Chip 8 Simulator"

#define COLS 64
#define ROWS 32

#define DEFAULT_SCALE 10

#define DEFAULT_WIN_WIDTH ((COLS) * (SCALE))
#define DEFAULT_WIN_HEIGHT ((ROWS) * (SCALE))

#define SCALE 10.0f
#define PIXEL_ON 1
#define PIXEL_OFF 0

#define FPS 60

int DISPLAY[ROWS * COLS] = {[0] = 1, [10] = 1, [2047]  = 1};

void set_color_black(SDL_Renderer *renderer)
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void set_color_white(SDL_Renderer *renderer)
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}

int display_set_pixel(int display[ROWS * COLS], int x, int y)
{
	x = (x + COLS) % COLS;
	y = (y + ROWS) % ROWS;
	display[x + y * COLS] ^= 1;
	return !display[x + y * COLS];
}

void display_clear(int display[ROWS * COLS])
{
	for (size_t i = 0; i < ROWS * COLS; ++i) {
		display[i] = 0;
	}
}

void display_render(SDL_Window *window, SDL_Renderer *renderer,
		    int display[ROWS * COLS])
{
	int h, w;
	SDL_GetWindowSize(window, &w, &h);
	for (size_t i = 0; i < COLS; ++i) {
		for (size_t j = 0; j < ROWS; ++j) {
			int pixel_val = display[i + j * COLS];
			if (pixel_val == PIXEL_ON) {
				set_color_white(renderer);
			} else if (pixel_val == PIXEL_OFF) {
				set_color_black(renderer);
			}
			SDL_RenderDrawPoint(renderer, i, j);
		}
	}
}

int scc(int code)
{
	if (code < 0) {
		fprintf(stderr, "SDL error: %s\n", SDL_GetError());
		exit(0);
	} else {
		return code;
	}
}

void *scp(void *ptr)
{
	if (ptr == NULL) {
		fprintf(stderr, "SDL error: %s]n", SDL_GetError());
		exit(0);
	} else {
		return ptr;
	}
}

int main(int argc, char **argv)
{
	scc(SDL_Init(SDL_INIT_VIDEO));

	SDL_Window *const window = scp(SDL_CreateWindow(
	    WINDOW_TITLE, 0, 0, DEFAULT_WIN_WIDTH, DEFAULT_WIN_HEIGHT, SDL_WINDOW_RESIZABLE));

	SDL_Renderer *const renderer =
	    scp(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED));

	scc(SDL_RenderSetLogicalSize(renderer, COLS, ROWS));

	int quit = 0;
	while (!quit) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT: {
				quit = 1;
			} break;
			}
		}

		scc(SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255));
		scc(SDL_RenderClear(renderer));
		display_render(window, renderer, DISPLAY);
		SDL_RenderPresent(renderer);
		sleep(1 / FPS);
	}

	SDL_Quit();
	return 0;
}
