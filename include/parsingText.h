#ifndef H_PARSINGTEXT
#define H_PARSINGTEXT

#include <stdbool.h>
#include <stdlib.h>

bool readText();

void printText();

bool workWithBuffer();

char* cleanLine( char* lineFromText );

void changeLine( char** firstLine, char** secondLine);

void doSwap( char* line_1, char* line_2, const size_t Size );

void getArrayOfStr( char** arrayOfStr, char* buffer,  size_t fileSize, char simvol );

size_t getSizeStrArray( char* buffer, size_t fileSize, char simvol );

void sortByFirstLetter( char** arrayOfStr, size_t arrayStrSize );

void sortByLastLetter( char** arrayOfStr, size_t arrayStrSize );

size_t printfForFile( char** arrayOfStr, size_t arrayStrSize, char* key, const char* mode);

size_t getFileSize();

void getOriginalText( char* bufferFromFile, size_t fileSize );

#endif