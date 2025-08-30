#ifndef H_ALLFUNCTION
#define H_ALLFUNCTION

#include <stdio.h>
#include <unistd.h>

int myPuts( const char* line );

char* myStrchr( const char* line, int ch );

size_t myStrlen( const char* line );

char* myStrcpy( char* strDestination, const char *strSource );

char* myStrncpy( char *strDest, const char *strSource, size_t count );

char* myStrcat( char* strDestination, const char* strSource );

char* myStrncat( char* strDestination, const char* strSource, size_t count );

char* myFgets( char* str, int numChars, FILE* stream );

char* myStrdup( const char* line );

ssize_t myGetline( char** line, size_t* n, FILE* stream );

#endif