#ifndef ALGORITHM_GUARD__H
#define ALGORITHM_GUARD__H

#define unitSize 10

int horizontalWidth, verticalHeight;
int screenWidth, screenHeight;

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