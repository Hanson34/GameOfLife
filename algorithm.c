#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>

#include "algorithm.h"

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
