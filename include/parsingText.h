#ifndef H_PARSINGTEXT
#define H_PARSINGTEXT

#include <stdbool.h>
#include <stdlib.h>

bool readText();

void printText();

char* cleanLine( char* lineFromText );

void changeLine( char** firstLine, char** secondLine);

void doSwap( char** line_1, char** line_2, const size_t Size );

#endif