#ifndef H_PARSINGTEXT
#define H_PARSINGTEXT

#include <stdbool.h>

bool ReadText();

char* cleanLine( char* lineFromText );

void changeLine( char** firstLine, char** secondLine);

#endif