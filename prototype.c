#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>

#include "prototype.h"

#define unitSize 10

//int horizontalWidth, verticalHeight;
//int screenWidth, screenHeight;

int main(int argc, char *argv[]){
	int option, w, h;
	printf("\nWelcome to Game of Life\n1. New Game\n2. Load Game\n3. Quit\nEnter the option: ");
    scanf("%d", &option);
    getchar();
    if(option==1){
		printf("\nEnter the width and height(width*height) you want: ");
		scanf("%d*%d",&w, &h);
		getchar();
		horizontalWidth=w;
		verticalHeight=h;
		int unit[verticalHeight][horizontalWidth];
	    for(int unitY = 0; unitY < verticalHeight; unitY++)
	        for(int unitX = 0; unitX < horizontalWidth; unitX++)
	            unit[unitY][unitX] = 0;
		screenWidth=w*unitSize;
		screenHeight=h*unitSize;
		sdlEvent(unit);
	}
	if(option==2){
		int s;
		int count=0;
	    FILE *st = fopen("state.txt","r+");
	    if(st==NULL)
	        return -1;
	    while(1){
	    	s=fgetc(st);
	    	if(s!='\n')
	    		count++;
	    	else
	    		break;
		}
		fclose(st);
		horizontalWidth=count;
		verticalHeight=count;
		screenWidth=horizontalWidth*unitSize;
		screenHeight=verticalHeight*unitSize;
		FILE *st1 = fopen("state.txt","r+");
		int unit[verticalHeight][horizontalWidth];
	    for(int y = 0; y < verticalHeight; y++){
	        for(int x = 0; x < horizontalWidth; x++){
				s=fgetc(st1);
				if(s==48)
					unit[y][x] = 0;
				else
					unit[y][x] = 1;
			}
			fscanf(st1,"%c",&s);
		}
		fclose(st1);
		sdlEvent(unit);
	}
	return 0;
}

void sdlEvent(int cell[][horizontalWidth])
{
	SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *w=sdlWindow("GoL");
    SDL_Renderer *r=rRenderer(w);
    SDL_Event e;
    bool clickL=false;
    bool clickR=false;
     while(1){
        while(SDL_PollEvent(&e)!=0){
            switch(e.type){
                case SDL_QUIT:
                    return;
                case SDL_MOUSEBUTTONDOWN:
					case SDL_MOUSEBUTTONUP:
                		switch(e.button.button){
		                    case SDL_BUTTON_LEFT:
								clickL=!clickL;
								break;
		                    case SDL_BUTTON_RIGHT:
								clickR=!clickR;
								break;
		                }
                case SDL_KEYDOWN:
                    if(e.key.keysym.sym==SDLK_SPACE)
	                evolve(cell);
	                saveState(cell);
            }
        }
    	int inputX, inputY;
        SDL_GetMouseState(&inputX, &inputY);
        if(clickL==true)
            cell[inputY/unitSize][inputX/unitSize]=1;
        else if(clickR==true)
            cell[inputY/unitSize][inputX/unitSize]=0;
        SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
        SDL_RenderClear(r);
        drawPlate(r);
        drawCell(r, cell);
        SDL_RenderPresent(r);
    }
    SDL_Quit();
}

SDL_Window *sdlWindow(char *title)
{
    SDL_Window *w=SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, 0);
	if(w==NULL){
        printf("\nWindow not created\n%s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    return w;
}

SDL_Renderer *rRenderer(SDL_Window *w)
{
    SDL_Renderer *r = SDL_CreateRenderer(w, -1, SDL_RENDERER_ACCELERATED);
	if(r==NULL){
        printf("\nRenderer not created\n%s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    return r;
}

void drawPlate(SDL_Renderer *r)
{
    for(int v=unitSize; v<screenWidth; v+=unitSize){
        SDL_SetRenderDrawColor(r, 100, 100, 100, 100);
        SDL_RenderDrawLine(r, v, 0, v, screenHeight);
    }
    for(int h=unitSize; h<screenHeight; h+=unitSize){
        SDL_SetRenderDrawColor(r, 100, 100, 100, 100);
        SDL_RenderDrawLine(r, 0, h, screenWidth, h);
    }
}

void drawCell(SDL_Renderer *r, int cell[][horizontalWidth])
{
    SDL_Rect unit;
    unit.w=unitSize+1;
    unit.h=unitSize+1;
    for(int uY=0; uY<verticalHeight; uY++){
        for(int uX=0; uX<horizontalWidth; uX++){
            if(cell[uY][uX]==1){
                unit.x = uX * unitSize;
                unit.y = uY * unitSize;
                SDL_SetRenderDrawColor(r, 250, 160, 0, 110);
                SDL_RenderFillRect(r, &unit);
            }
        }
    }
}

//void evolve(int cell[][horizontalWidth])
//{
//	int buf[verticalHeight][horizontalWidth];
//	int neighbour;
//    for(int j=0; j<horizontalWidth; j++){
//        for(int i=0; i<verticalHeight; i++){
//            neighbour=0;
//            if(i==0){
//                if(j==0)
//                    neighbour=cell[i][j+1]+cell[i+1][j]+cell[i+1][j+1];
//                else if(j==horizontalWidth-1)
//                    neighbour=cell[i][j-1]+cell[i+1][j]+cell[i+1][j-1];
//                else
//                    neighbour=cell[i][j-1]+cell[i+1][j-1]+cell[i][j+1]+cell[i+1][j]+cell[i+1][j+1];
//            }
//            else if(i==verticalHeight-1){
//                if(j==0)
//                    neighbour=cell[i][j+1]+cell[i-1][j]+cell[i-1][j+1];
//                else if(j==horizontalWidth-1)
//                    neighbour=cell[i][j-1]+cell[i-1][j]+cell[i-1][j-1];
//                else
//                    neighbour=cell[i][j-1]+cell[i-1][j-1]+cell[i][j+1]+cell[i-1][j]+cell[i-1][j+1];
//            }
//            else if(j==0)
//                neighbour=cell[i-1][j]+cell[i-1][j+1]+cell[i][j+1]+cell[i+1][j+1]+cell[i+1][j];
//            else if(j==horizontalWidth-1)
//                neighbour=cell[i-1][j]+cell[i-1][j-1]+cell[i][j-1]+cell[i+1][j-1]+cell[i+1][j];
//            else
//                neighbour=cell[i-1][j]+cell[i-1][j-1]+cell[i][j-1]+cell[i+1][j-1]+cell[i+1][j]+cell[i-1][j+1]+cell[i][j+1]+cell[i+1][j+1];
//            if(neighbour==3)
//                buf[i][j]=1;
//            else if(neighbour==2)
//                buf[i][j]=cell[i][j];
//            else
//                buf[i][j]==0;
//        }
//    }
//    for(int j=0; j<horizontalWidth; j++)
//        for(int i=0; i<verticalHeight; i++)
//        	cell[i][j]=buf[i][j];
//}

int saveState(int cell[][horizontalWidth])
{
	int s;
    FILE *st = fopen("state.txt","w+");
    if(st==NULL)
        return -1;
    for(int y = 0; y < verticalHeight; y++){
        for(int x = 0; x < horizontalWidth; x++)
			fprintf(st, "%d", cell[y][x]);
		fprintf(st,"\n");
	}
	fclose(st);
	return 0;
}

int loadState()
{
	int s, count=0;
    FILE *st = fopen("state.txt","r+");
    if(st==NULL)
        return -1;
    while(1){
    	fscanf(st, "%d", &s);
    	if(s!='\0')
    		count++;
    	else
    		break;
	}
	int cell[count][count];
    for(int y = 0; y < count; y++){
        for(int x = 0; x < count; x++){
			fscanf(st, "%d", &s);
			if(s==0)
				cell[y][x] = 0;
			else
				cell[y][x] = 1;
		}
		fscanf(st,"%c",&s);
	}
	fclose(st);
	return count;
}

void evolve(int cell[][horizontalWidth]){
    int new[verticalHeight][horizontalWidth];
    int cy, cx;
    for(cy = 0; cy < verticalHeight; cy++){
        for(cx = 0; cx < horizontalWidth; cx++){
            if(cell[cy][cx] == 1 && calculateNeighbour(cell, cx, cy) < 2)
                new[cy][cx] = 0;
            else if(cell[cy][cx] == 1 && (calculateNeighbour(cell, cx, cy) == 2 || calculateNeighbour(cell, cx, cy) == 3))
                new[cy][cx] = 1;
            else if(cell[cy][cx] == 1 && calculateNeighbour(cell, cx, cy) > 3)
                new[cy][cx] = 0;
            else if(cell[cy][cx] == 0 && calculateNeighbour(cell, cx, cy) == 3)
                new[cy][cx] = 1;

            else
                new[cy][cx] = 0;
        }
    }
    for(cy = 0; cy < verticalHeight; cy++){
        for(cx = 0; cx < horizontalWidth; cx++){
            cell[cy][cx] = new[cy][cx];
        }
    }
}

int calculateNeighbour(int cell[][horizontalWidth], int x, int y){
    int count = 0, cx, cy;
    for(cy = y - 1; cy <= y + 1; cy++){
        for(cx = x - 1; cx <= x + 1; cx++){
            if(!(cy < 0 || cx < 0 || cy >= verticalHeight || cx >= horizontalWidth)){
                if(cell[cy][cx] == 1)
                    count++;
                if(cell[cy][cx] == 1 && cx == x && cy == y)
                    count--;
            }
        }
    }
    return count;
}

