#include "unity.h"
#include "../interface.h"
#include "../algorithm.h"
#include "../sdlevents.h"

int horizontalWidth=50, verticalHeight=50;
int screenWidth=500, screenHeight=500;

void test_saveState(){
	int unit[50][50]={0};
	int result;
	result=saveState(unit);
	TEST_ASSERT_EQUAL_INT_MESSAGE(0, result, "Failed to save the state");
	FILE *st = fopen("state.txt","r+");
	int s=fgetc(st);
	TEST_ASSERT_EQUAL_INT_MESSAGE(48, s, "Wrong saving process");
	fclose(st);
}

void test_evolve(){
	int unit[50][50]={0};
	evolve(unit);
	int result;
	for(int i=0; i<50;i++){
		result=unit[i][0];
		TEST_ASSERT_EQUAL_INT_MESSAGE(0, result, "Evolution go wrong");
	}
	unit[1][2]=1;
	unit[2][0]=1;
	unit[2][2]=1;
	unit[3][1]=1;
	unit[3][2]=1;
	evolve(unit);
	TEST_ASSERT_EQUAL_INT_MESSAGE(0, unit[2][0], "Evolution go wrong");
	TEST_ASSERT_EQUAL_INT_MESSAGE(0, unit[1][2], "Evolution go wrong");
	TEST_ASSERT_EQUAL_INT_MESSAGE(1, unit[1][1], "Evolution go wrong");
	TEST_ASSERT_EQUAL_INT_MESSAGE(1, unit[2][3], "Evolution go wrong");
}

void test_calculateNeighbour(){
	int unit[50][50]={0};
	int result;
	for(int i=0; i<50;i++){
		result=calculateNeighbour(unit, i, 0);
		TEST_ASSERT_EQUAL_INT_MESSAGE(0, result, "Calculation wrong");
	}
	unit[1][2]=1;
	unit[2][0]=1;
	unit[2][2]=1;
	unit[3][1]=1;
	unit[3][2]=1;
	TEST_ASSERT_EQUAL_INT_MESSAGE(5, calculateNeighbour(unit, 1, 2), "Calculation wrong");
	TEST_ASSERT_EQUAL_INT_MESSAGE(1, calculateNeighbour(unit, 2, 0), "Calculation wrong");
	TEST_ASSERT_EQUAL_INT_MESSAGE(3, calculateNeighbour(unit, 2, 2), "Calculation wrong");
	TEST_ASSERT_EQUAL_INT_MESSAGE(2, calculateNeighbour(unit, 3, 1), "Calculation wrong");
	TEST_ASSERT_EQUAL_INT_MESSAGE(3, calculateNeighbour(unit, 3, 2), "Calculation wrong");
}

void test_sdlWindow(){
	char *title="title";
	TEST_ASSERT_EQUAL_INT_MESSAGE(500, screenWidth, "Parameters wrong");
//	SDL_Window *result=SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, 0);
	SDL_Window *result=sdlWindow(title);
	TEST_ASSERT_NOT_NULL_MESSAGE(result, "Wrong generation of SDL window");
}

void test_rRenderer(){
	char *title="title";
	SDL_Window *win=SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, 0);
//	SDL_Renderer *r=SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	SDL_Renderer *r=rRenderer(win);
	TEST_ASSERT_NOT_NULL_MESSAGE(r, "Wrong renderer of SDL window");
}

void setUp() {
	 //this function is called before each test, it can be empty
}

void tearDown() {
	 //this function is called after each test, it can be empty
}

int main(int argc, char *argv[]){
	UNITY_BEGIN();
	RUN_TEST(test_saveState);
	RUN_TEST(test_evolve);
	RUN_TEST(test_calculateNeighbour);
	RUN_TEST(test_sdlWindow);
	RUN_TEST(test_rRenderer);
	return UNITY_END();
}
