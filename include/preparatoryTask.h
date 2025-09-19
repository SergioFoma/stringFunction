#ifndef H_PREPARATORYTASK
#define H_PREPARATORYTASK

#include <stdlib.h>

bool readText();

void printText();

void changeLine( char** firstLine, char** secondLine);

void doSwap( char* line_1, char* line_2, const size_t Size );
#endif