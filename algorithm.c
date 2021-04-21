#include <stdio.h>
#include <SDL.h>

int I, J;
int state1[I][J]={0};
int state2[I][J]={0};
int filp = 1;

int load_state()
{
    char s;
    FILE *st = fopen("state.txt","r+");
    if(st==NULL){
        return -1;
    }
    for(int i=0; i<I; i++){
		for(int j=0; j<J; j++){
			fscanf(st, "%c", &s);
			if(s!="*"){
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
	return 0;
}

void evolve(int map1[I][J],int map2[I][J])
{
    int neighbour;
    for(int i=0; i<I; i++){
        for(int j=0; j<J; j++){
            neighbour=0;
            if(i==0){
                if(j==0)
                    neighbour=map1[i][j+1]+map1[i+1][j]+map1[i+1][j+1];
                else if(j==J-1)
                    neighbour=map1[i][j-1]+map1[i+1][j]+map1[i+1][j-1];
                else
                    neighbour=map1[i][j-1]+map1[i+1][j-1]+map1[i][j+1]+map1[i+1][j]+map1[i+1][j+1];
            }
            else if(i==I-1){
                if(j==0)
                    neighbour=map1[i][j+1]+map1[i-1][j]+map1[i-1][j+1];
                else if(j==J-1)
                    neighbour=map1[i][j-1]+map1[i-1][j]+map1[i-1][j-1];
                else
                    neighbour=map1[i][j-1]+map1[i-1][j-1]+map1[i][j+1]+map1[i-1][j]+map1[i-1][j+1];
            }
            else if(j==0)
                neighbour=map1[i-1][j]+map1[i-1][j+1]+map1[i][j+1]+map1[i+1][j+1]+map1[i+1][j];
            else if(j==J-1)
                neighbour=map1[i-1][j]+map1[i-1][j-1]+map1[i][j-1]+map1[i+1][j-1]+map1[i+1][j];
            else
                neighbour=map1[i-1][j]+map1[i-1][j-1]+map1[i][j-1]+map1[i+1][j-1]+map1[i+1][j]+map1[i-1][j+1]+map1[i][j+1]+map1[i+1][j+1];
            if(neighbour==3)
                map2[i][j]=1;
            else if(neighbour==2)
                map2[i][j]=map1[i][j];
            else
                map2[i][j]==0;
        }
    }
}

void filp()
{
    if(filp==1){
        evolve(state1[I][J], state2[I],[J]);
        filp=2;
    }
    else if(filp==2){
        evolve(state2[I][J], state1[I],[J]);
        filp=1;
    }
}

void run_game()
{
    if(load_state==-1)
        return;
    while(1){
    }

}