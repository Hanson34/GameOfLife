#ifndef PROTOTYPE_GUARD__H
#define PROTOTYPE_GUARD__H

#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>

int horizontalWidth, verticalHeight;
int screenWidth, screenHeight;

void sdlEvent(int cell[][horizontalWidth]); 
SDL_Window *sdlWindow(char *title);
SDL_Renderer *rRenderer(SDL_Window *w);
void drawPlate(SDL_Renderer *r);
void drawCell(SDL_Renderer *r, int cell[][horizontalWidth]);
void evolve(int cell[][horizontalWidth]);
int calculateNeighbour(int cell[][horizontalWidth], int x, int y);
int saveState(int cell[][horizontalWidth]);
int loadState();

#endif