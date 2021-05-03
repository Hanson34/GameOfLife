#ifndef INTERFACE_GUARD__H
#define INTERFACE_GUARD__H

#define unitSize 10

int horizontalWidth, verticalHeight;
int screenWidth, screenHeight;

//interface to enter command
int runInterface();

//choose whether run by step or wildly
int stepOrWild();

//SDL events containing the following ones
void sdlEvent(int cell[verticalHeight][horizontalWidth], int c);

#endif