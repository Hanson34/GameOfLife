<<<<<<< HEAD
#include <stdio.h>
#include <SDL.h>

#include "interface.h"

#define maxI 1000
#define maxJ 1000

int state1[maxI][maxJ]={0};
int state2[maxI][maxJ]={0};
int flip=1;
int option;
int w, h;

void run_interface()
{
    printf("\nWelcome to Game of Life\n1. New Game\n2. Load Game\n3. Quit\nEnter the option: ");
    scanf("%d", &option);
    getchar();
    switch(option){
    	case 1:
    		printf("\nEnter the width and height(width*height) you want: ");
    		scanf("%d*%d",&w, &h);
    		getchar();
    		new_state(w, h);
	}
}

int end_status()
{
	int num;
	while(1){
		printf("\n!. Run until terminate\n2. Run for certain step\nEnter the option: ");
		scanf("%d", &num);
		getchar();
		if(num==1)
			return 0;
		else if(num==2){
			printf("\nEnter the step you want to evolve: ");
			scanf("%d", &num);
			getchar();
			return num;
		}
		else
			printf("\nInvalid input\n");
	}
}

int new_state(int w, int h)
{
	for(int i=0; i<w; i++){
		for(int j=0; j<h; j++){
			state1[i][j] = 0;
		    state2[i][j] = 0;
		}
	}
	flip=1;
	return 0;
}

int load_state()
{
	int s;
    FILE *st = fopen("state.txt","r+");
    if(st==NULL){
        return -1;
    }
    for(int i=0; i<w; i++){
		for(int j=0; j<h; j++){
			fscanf(st, "%d", &s);
			if(s==0){
				state1[i][j] = 0;
			    state2[i][j] = 0;
			}
			else{
				state1[i][j] = 1;
			    state2[i][j] = 1;
			}
		}
		fscanf(st,"%c",&s);
	}
	flip=1;
	return 0;
}

int save_state()
{
	int s;
    FILE *st = fopen("state.txt","w+");
    if(st==NULL){
        return -1;
    }
    for(int i=0; i<w; i++){
		for(int j=0; j<h; j++){
			if(flip==1)
				fprintf(st, "%d", state1[i][j]);
			else
				fprintf(st, "%d", state2[i][j]);
		}
		fprintf(st,"\n");
	}
	flip=1;
	return 0;
}

void evolve(int ss)
{
    int neighbour;
    if(ss==1){
	    for(int i=0; i<w; i++){
	        for(int j=0; j<h; j++){
	            neighbour=0;
	            if(i==0){
	                if(j==0)
	                    neighbour=state1[i][j+1]+state1[i+1][j]+state1[i+1][j+1];
	                else if(j==h-1)
	                    neighbour=state1[i][j-1]+state1[i+1][j]+state1[i+1][j-1];
	                else
	                    neighbour=state1[i][j-1]+state1[i+1][j-1]+state1[i][j+1]+state1[i+1][j]+state1[i+1][j+1];
	            }
	            else if(i==w-1){
	                if(j==0)
	                    neighbour=state1[i][j+1]+state1[i-1][j]+state1[i-1][j+1];
	                else if(j==h-1)
	                    neighbour=state1[i][j-1]+state1[i-1][j]+state1[i-1][j-1];
	                else
	                    neighbour=state1[i][j-1]+state1[i-1][j-1]+state1[i][j+1]+state1[i-1][j]+state1[i-1][j+1];
	            }
	            else if(j==0)
	                neighbour=state1[i-1][j]+state1[i-1][j+1]+state1[i][j+1]+state1[i+1][j+1]+state1[i+1][j];
	            else if(j==h-1)
	                neighbour=state1[i-1][j]+state1[i-1][j-1]+state1[i][j-1]+state1[i+1][j-1]+state1[i+1][j];
	            else
	                neighbour=state1[i-1][j]+state1[i-1][j-1]+state1[i][j-1]+state1[i+1][j-1]+state1[i+1][j]+state1[i-1][j+1]+state1[i][j+1]+state1[i+1][j+1];
	            if(neighbour==3)
	                state2[i][j]=1;
	            else if(neighbour==2)
	                state2[i][j]=state1[i][j];
	            else
	                state2[i][j]==0;
	        }
	    }
	}
	flip=2;
	if(ss==2){
	    for(int i=0; i<w; i++){
	        for(int j=0; j<h; j++){
	            neighbour=0;
	            if(i==0){
	                if(j==0)
	                    neighbour=state2[i][j+1]+state2[i+1][j]+state2[i+1][j+1];
	                else if(j==h-1)
	                    neighbour=state2[i][j-1]+state2[i+1][j]+state2[i+1][j-1];
	                else
	                    neighbour=state2[i][j-1]+state2[i+1][j-1]+state2[i][j+1]+state2[i+1][j]+state2[i+1][j+1];
	            }
	            else if(i==w-1){
	                if(j==0)
	                    neighbour=state2[i][j+1]+state2[i-1][j]+state2[i-1][j+1];
	                else if(j==h-1)
	                    neighbour=state2[i][j-1]+state2[i-1][j]+state2[i-1][j-1];
	                else
	                    neighbour=state2[i][j-1]+state2[i-1][j-1]+state2[i][j+1]+state2[i-1][j]+state2[i-1][j+1];
	            }
	            else if(j==0)
	                neighbour=state2[i-1][j]+state2[i-1][j+1]+state2[i][j+1]+state2[i+1][j+1]+state2[i+1][j];
	            else if(j==h-1)
	                neighbour=state2[i-1][j]+state2[i-1][j-1]+state2[i][j-1]+state2[i+1][j-1]+state2[i+1][j];
	            else
	                neighbour=state2[i-1][j]+state2[i-1][j-1]+state2[i][j-1]+state2[i+1][j-1]+state2[i+1][j]+state2[i-1][j+1]+state2[i][j+1]+state2[i+1][j+1];
	            if(neighbour==3)
	                state1[i][j]=1;
	            else if(neighbour==2)
	                state1[i][j]=state2[i][j];
	            else
	                state1[i][j]==0;
	        }
	    }
	}
	flip=1;
}

//void filp_state()
//{
//    if(filp==1){
//        evolve(state1[I][J], state2[I][J]);
//        filp=2;
//    }
//    else if(filp==2){
//        evolve(state2[I][J], state1[I][J]);
//        filp=1;
//    }
//}
=======
#include <stdio.h>

#include "interface.h"
#include "algorithm.h"

void run_interface()
{
    
}
>>>>>>> a12903f648f3de12abef264d655fa1b44b794950
