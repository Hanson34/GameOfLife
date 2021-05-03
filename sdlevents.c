#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>

#include "sdlevents.h"

SDL_Window *sdlWindow(char *title){
	//SDL_Window * SDL_CreateWindow(const char *title, int x, int y, int w, int h, Uint32 flags);
    SDL_Window *w=SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, 0);
	if(w==NULL){
        printf("\nWindow not created\n%s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    return w;
}

SDL_Renderer *rRenderer(SDL_Window *w){
	//SDL_Renderer * SDL_CreateRenderer(SDL_Window * window, int index, Uint32 flags);
    SDL_Renderer *r=SDL_CreateRenderer(w, -1, SDL_RENDERER_ACCELERATED);
	if(r==NULL){
        printf("\nRenderer not created\n%s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    return r;
}

void drawPlate(SDL_Renderer *r){
    for(int v=unitSize; v<screenWidth; v+=unitSize){
    	//int SDL_SetRenderDrawColor(SDL_Renderer * renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
        SDL_SetRenderDrawColor(r, 10, 10, 10, 255);
        //int SDL_RenderDrawLine(SDL_Renderer * renderer, int x1, int y1, int x2, int y2);
        SDL_RenderDrawLine(r, v, 0, v, screenHeight);
    }
    for(int h=unitSize; h<screenHeight; h+=unitSize){
        SDL_SetRenderDrawColor(r, 10, 10, 10, 255);
        SDL_RenderDrawLine(r, 0, h, screenWidth, h);
    }
}

void drawCell(SDL_Renderer *r, int cell[verticalHeight][horizontalWidth]){
    SDL_Rect unit;
    unit.w=unitSize+1;
    unit.h=unitSize+1;
    for(int uY=0; uY<verticalHeight; uY++){
        for(int uX=0; uX<horizontalWidth; uX++){
            if(cell[uY][uX]==1){
                unit.x=uX*unitSize;
                unit.y=uY*unitSize;
                SDL_SetRenderDrawColor(r, 10, 10, 10, 255);
                //int SDL_RenderFillRect(SDL_Renderer * renderer, const SDL_Rect * rect);
                SDL_RenderFillRect(r, &unit);
            }
        }
    }
}