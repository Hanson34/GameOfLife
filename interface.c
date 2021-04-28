#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>

#include "interface.h"

int runInterface(){
	int option, w, h;
		printf("\nWelcome to Game of Life\n\nPress enter to evolve single step;\nPress space to evolve continuously;\nPress up to speed up;\nPress down to solwn down;\nPress backspace to clear the screen\n\n1. New Game\n2. Load Game\n3. Quit\nEnter the option: ");
	    scanf("%d", &option);
	    getchar();
	    //create a new game
	    if(option==1){
	    	//set up the world range
			printf("\nEnter the width and height(width*height) you want: ");
			scanf("%d*%d",&w, &h);
			getchar();
			horizontalWidth=w;
			verticalHeight=h;
			//initialize the cell unit
			int unit[verticalHeight][horizontalWidth];
		    for(int unitY = 0; unitY < verticalHeight; unitY++)
		        for(int unitX = 0; unitX < horizontalWidth; unitX++)
		            unit[unitY][unitX] = 0;
		    //set up the SDL window size
			screenWidth=w*unitSize;
			screenHeight=h*unitSize;
			//continue working...
			sdlEvent(unit);
		}
		else if(option==2){
			int s;
			int count=0;
			//read world size from file
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
			//set up the SDL window size
			horizontalWidth=count;
			verticalHeight=count;
			screenWidth=horizontalWidth*unitSize;
			screenHeight=verticalHeight*unitSize;
			//extract from existing file to load the cell world
			//0 stands for dead, 1 stands for alive
			FILE *st1 = fopen("state.txt","r+");
			int unit[verticalHeight][horizontalWidth];
		    for(int y=0; y<verticalHeight; y++){
		        for(int x=0; x<horizontalWidth; x++){
					s=fgetc(st1);
					if(s==48)
						unit[y][x] = 0;
					else
						unit[y][x] = 1;
				}
				fscanf(st1,"%c",&s);
			}
			fclose(st1);
			//continue working...
			sdlEvent(unit);
		}
		return 0;
}

void sdlEvent(int cell[verticalHeight][horizontalWidth]){
	SDL_Init(SDL_INIT_VIDEO);
	//create and render the SDL window
    SDL_Window *w=sdlWindow("GoL");
    SDL_Renderer *r=rRenderer(w);
    SDL_Event e;
    bool clickL=false;
    bool clickR=false;
    bool pause=true;
    int tick=1000;
    int t=0;
//    int option;
//    printf("\n1. Evolve at will\n 2. Evolve centain steps\nEnter the choice: ");
//    scanf("%d", &option);
//	getchar();
//	if(option==2){
//		printf("\nEnter the steps: ");
//		scanf("%d", &option);
//		getchar();
//		for(int i=0; i<option; i++){
//			if(SDL_GetTicks()-t>=tick){
//				evolve(cell);
//				saveState(cell);
//				t=SDL_GetTicks();
//			}
//		}
//	}
    while(1){
        while(SDL_PollEvent(&e)!=0){
            switch(e.type){
                case SDL_QUIT:
                    return;
                //left click to make cell alive, right click to make it dead
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
                	//press enter to evolve
                    if(e.key.keysym.sym==SDLK_RETURN)
	                evolve(cell);
	                saveState(cell);
	                //press backspace to clear the screen
	                if(e.key.keysym.sym==SDLK_BACKSPACE)
		            for(int unitY=0; unitY<verticalHeight; unitY++)
		        		for(int unitX=0; unitX<horizontalWidth; unitX++)
		            		cell[unitY][unitX] = 0;
		            //press space to start/pause the process
		            if(e.key.keysym.sym==SDLK_SPACE){
		            	if(pause==true){
		            		pause=false;
		            		break;
						}
						if(pause==false){
							pause=true;
							break;
						}
					}
					//press up/down to change speed
					if(e.key.keysym.sym==SDLK_UP)
						tick=100;
					if(e.key.keysym.sym==SDLK_DOWN)
						tick=1000;
            }
        }
		if(SDL_GetTicks()-t>=tick&&pause==false){
			evolve(cell);
			saveState(cell);
			t=SDL_GetTicks();
		}
        //render to SDL window
    	int inputX, inputY;
        SDL_GetMouseState(&inputX, &inputY);
        if(clickL==true)
            cell[inputY/unitSize][inputX/unitSize]=1;
        else if(clickR==true)
            cell[inputY/unitSize][inputX/unitSize]=0;
        SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
        //clear the renderer
        SDL_RenderClear(r);
        //redraw the plate
        drawPlate(r);
        drawCell(r, cell);
        SDL_RenderPresent(r);
    }
    //quit when press the x or the window
    SDL_Quit();
}

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

int saveState(int cell[verticalHeight][horizontalWidth]){
	int s;
    FILE *st = fopen("state.txt","w+");
    if(st==NULL)
        return -1;
    for(int y=0; y<verticalHeight; y++){
        for(int x=0; x<horizontalWidth; x++)
			fprintf(st, "%d", cell[y][x]);
		fprintf(st,"\n");
	}
	fclose(st);
	return 0;
}

//have not used this function!
int loadState(){
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

void evolve(int cell[verticalHeight][horizontalWidth]){
	/*1. Any live cell with 0 or 1 live neighbours becomes dead because of underpopulation
	2. Any live cell with 2 or 3 live neighbours stays alive because its neighbourhood is just right
	3. Any live cell with more than 3 live neighbours becomes dead because of overpopulation
	4. Any dead cell with exactly 3 live neighbours becomes alive by reproduction*/
	//In short, any cell with 3 around become alive, any cell with 2 stay the same, others become dead
    int buf[verticalHeight][horizontalWidth];
    for(int y=0; y<verticalHeight; y++){
        for(int x=0; x<horizontalWidth; x++){
            if(calculateNeighbour(cell, x, y)==3)
                buf[y][x]=1;
            else if(calculateNeighbour(cell, x, y)==2)
                buf[y][x]=cell[y][x];
            else
                buf[y][x]=0;
        }
    }
    //transfer buf state to cell
    for(int y=0; y<verticalHeight; y++){
        for(int x=0; x<horizontalWidth; x++){
            cell[y][x]=buf[y][x];
        }
    }
}
 
int calculateNeighbour(int cell[verticalHeight][horizontalWidth], int X, int Y){
    int neighbour=0;
    for(int y=Y-1; y<=Y+1; y++){
        for(int x=X-1; x<=X+1; x++){
            if(y>=0 && x>=0 && y<verticalHeight && x<horizontalWidth){
            	//count the neighbouring cells
                if(cell[y][x]==1)
                    neighbour++;
                //minus the cell itself
                if(cell[y][x]==1 && x==X && y==Y)
                    neighbour--;
            }
        }
    }
    return neighbour;
}

//void evolve(int cell[verticalHeight][horizontalWidth]){
//	int buf[verticalHeight][horizontalWidth];
//	int neighbour;
//    for(int y=0; y<verticalHeight; y++){
//        for(int x=0; x<horizontalWidth; x++){
//            neighbour=0;
//            if(y==0){
//                if(x==0)
//                    neighbour=cell[y][x+1]+cell[y+1][x]+cell[y+1][x+1];
//                else if(x==horizontalWidth-1)
//                    neighbour=cell[y][x-1]+cell[y+1][x]+cell[y+1][x-1];
//                else
//                    neighbour=cell[y][x-1]+cell[y+1][x-1]+cell[y][x+1]+cell[y+1][x]+cell[y+1][x+1];
//            }
//            else if(y==verticalHeight-1){
//                if(x==0)
//                    neighbour=cell[y][x+1]+cell[y-1][x]+cell[y-1][x+1];
//                else if(x==horizontalWidth-1)
//                    neighbour=cell[y][x-1]+cell[y-1][x]+cell[y-1][x-1];
//                else
//                    neighbour=cell[y][x-1]+cell[y-1][x-1]+cell[y][x+1]+cell[y-1][x]+cell[y-1][x+1];
//            }
//            else if(x==0)
//                neighbour=cell[y-1][x]+cell[y-1][x+1]+cell[y][x+1]+cell[y+1][x+1]+cell[y+1][x];
//            else if(x==horizontalWidth-1)
//                neighbour=cell[y-1][x]+cell[y-1][x-1]+cell[y][x-1]+cell[y+1][x-1]+cell[y+1][x];
//            else
//                neighbour=cell[y-1][x]+cell[y-1][x-1]+cell[y][x-1]+cell[y+1][x-1]+cell[y+1][x]+cell[y-1][x+1]+cell[y][x+1]+cell[y+1][x+1];
//            if(neighbour==3)
//                buf[y][x]=1;
//            else if(neighbour==2)
//                buf[y][x]=cell[y][x];
//            else
//                buf[y][x]==0;
//        }
//    }
//    for(int y=0; y<verticalHeight; y++)
//        for(int x=0; x<horizontalWidth; x++)
//        	cell[y][x]=buf[y][x];
//}
