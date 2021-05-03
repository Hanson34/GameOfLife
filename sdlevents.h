#ifndef SDLEVENTS_GUARD__H
#define SDLEVENTS_GUARD__H

#define unitSize 10

int horizontalWidth, verticalHeight;
int screenWidth, screenHeight;

//create SDL window
SDL_Window *sdlWindow(char *title);

//render SDL window
SDL_Renderer *rRenderer(SDL_Window *w);

//render checkboard texture on SDL window
void drawPlate(SDL_Renderer *r);

//when cell is alive, render the cell
void drawCell(SDL_Renderer *r, int cell[verticalHeight][horizontalWidth]);

#endif