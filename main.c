#include <stdio.h>
#include <SDL.h>
#include "automaton.h"

#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 900
#define UNIT_SIZE 1
#define BORDER_WIDTH 0
#define COLORED_AREA UNIT_SIZE - BORDER_WIDTH * 2

FILE * gErrorLog = 0;

SDL_Event e;
SDL_Window *gWindow = 0;
SDL_Surface *gWindowSurface = 0;
SDL_Renderer *gRenderer = 0;
SDL_Rect gDrawingRect;

void init();
void close();

void draw_automaton();
void clear_screen();
void color_cell(int x, int y);

int main(int argc, char * argv[])
{
    init();
    draw_automaton();

    int quit = 0;
    while(!quit) {
        while(!SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
        }
    }

    close();
    return 0;
}

void draw_automaton() {
    clear_screen();
    init_automaton();
    for (int i = 0; i < CELL_COUNT; i++) {
        for (int j = 0; j < CELL_COUNT; j++) {
            if (gCells[j]) {
                color_cell(j, i);
            }
        }

        next_iteration();
    }

    SDL_RenderPresent(gRenderer);
}

void clear_screen() {
    SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(gRenderer);
}

void color_cell(int x, int y) {
    gDrawingRect = (SDL_Rect){
        x * UNIT_SIZE + BORDER_WIDTH,
        y * UNIT_SIZE + BORDER_WIDTH,
        COLORED_AREA,
        COLORED_AREA
    };
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderFillRect(gRenderer, &gDrawingRect);
}

void init() {
    gErrorLog = fopen("errorlog.txt", "w+");
    SDL_Init(SDL_INIT_VIDEO);
    gWindow = SDL_CreateWindow("automata", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    gWindowSurface = SDL_GetWindowSurface(gWindow);
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
}

void close() {
    if (SDL_GetError()) {
        fputs(SDL_GetError(), gErrorLog);
    }

    fclose(gErrorLog);
    gErrorLog = 0;
    SDL_DestroyRenderer(gRenderer);
    gRenderer = 0;
    SDL_DestroyWindow(gWindow);
    gWindow = 0;
    SDL_Quit();
}