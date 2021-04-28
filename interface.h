#ifndef INTERFACE_GUARD__H
#define INTERFACE_GUARD__H

#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>

#define unitSize 10

int horizontalWidth, verticalHeight;
int screenWidth, screenHeight;

//interface to enter command
int runInterface();

//SDL part
//SDL events containing the following ones
void sdlEvent(int cell[verticalHeight][horizontalWidth]);

//create SDL window
SDL_Window *sdlWindow(char *title);

//render SDL window
SDL_Renderer *rRenderer(SDL_Window *w);

//render checkboard texture on SDL window
void drawPlate(SDL_Renderer *r);

//when cell is alive, render the cell
void drawCell(SDL_Renderer *r, int cell[verticalHeight][horizontalWidth]);

//ALgorithm part
//use a buf array to evolve the cells
void evolve(int cell[verticalHeight][horizontalWidth]);

//calculate the state of cell
int calculateNeighbour(int cell[verticalHeight][horizontalWidth], int x, int y);

//File IO part
//save currect cell[][] into txt
int saveState(int cell[verticalHeight][horizontalWidth]);

//load it into algorithms
int loadState();

#endif