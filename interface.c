#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>

#include "interface.h"
#include "sdlevents.h"
#include "algorithm.h"

int runInterface(){
	int option, w, h, c;
	printf("\nWelcome to Game of Life\n\nPress enter to evolve single step;\nPress space to evolve continuously;\nPress up to speed up;\nPress down to solwn down;\nPress backspace to clear the screen\n");
	while(1){
		printf("\n1. New Game\n2. Load Game\n3. Quit\nEnter the option: ");
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
			c=stepOrWild();
			sdlEvent(unit, c);
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
			c=stepOrWild();
			sdlEvent(unit, c);
		}
		else if(option==3)
			return 0;
		else
			printf("\nInvalid input\n");
	}
}

int stepOrWild(){
    int option;
    while(1){
    	printf("\n1. Evolve at will\n2. Evolve centain steps\nEnter the option: ");
	    scanf("%d", &option);
		getchar();
		if(option==1)
			return 0;
		else if(option==2){
			printf("\nEnter the steps: ");
			scanf("%d", &option);
			getchar();
			return option;
		}
		else
			printf("\nInvalid input\n");
	}
}

void sdlEvent(int cell[verticalHeight][horizontalWidth], int c){
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
    int count=0;
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
                    if(e.key.keysym.sym==SDLK_RETURN){
                		evolve(cell);
              			saveState(cell);
					}
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
        if(c!=0&&SDL_GetTicks()-t>=tick&&pause==false){
        	count++;
        	printf("%d", count);
        	if(count==c)
        		pause=true;
		}
    }
    //quit when press the x or the window
    SDL_Quit();
}
