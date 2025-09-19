#ifndef H_PARSINGTEXT
#define H_PARSINGTEXT

#include <stdbool.h>
#include <stdlib.h>

bool workWithBuffer();

void getArrayOfStr( char** arrayOfStr, char* buffer,  size_t fileSize, char simvol );

size_t getSizeStrArray( char* buffer, size_t fileSize, char simvol );

void sortByFirstLetter( char** arrayOfStr, size_t arrayStrSize );

void sortByLastLetter( char** arrayOfStr, size_t arrayStrSize );

size_t printfForFile( char** arrayOfStr, size_t arrayStrSize, char* key, const char* mode);

size_t getFileSize();

void getOriginalText( char* bufferFromFile, size_t fileSize );

int sortFirstLetter( const void* first, const void* second );

int sortLastLetter( const void* first, const void* second );

void myQsort( void* list, size_t count, size_t sizeInBytes, 
              int (*compare)(const void*, const void*) );
#endif