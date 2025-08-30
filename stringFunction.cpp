#include "allfunction.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main() {
	
	char array[] = "Hello Wolrd";
	
	myPuts( "Hello world" );
	
	char* res = myStrchr( "Hello World", 'e' );
	
	if ( res == NULL ) printf( "NULL" );
	else printf("%c", *res );
	
	printf("\n%u", myStrlen( "Hello, world!" ) );
	
	char copy_line[ 50 ] = "";
	const char* line = "Hello world from strcpy";
	
	char* result = myStrcpy( copy_line, line );
	printf("\n%s", result );

    char copyLine[ 50 ] = "";
    const char* Line = "Hello world from strncpy";

    result = myStrncpy( copyLine, Line, 10 );
    printf("\n%s", result );

    char first[ 50 ] = "Hello";
    const char second[] = " World from strcat";

    char* Result = myStrcat( first, second );
    printf("\n%s", Result );

    char First[ 50 ] = "Hello";
    const char Second[] = " World from strncat";

    char* Res = myStrncat( First, Second, myStrlen( Second ) );
    printf("\n%s", Res );

    FILE* fileName = fopen( "TestStrFunction.txt", "r");

    if ( fileName == NULL ) {
        printf( "\nОшибка открытия файла" );
    }
    char place[50] = "";
    char* resultFromFile = myFgets( place, sizeof( place ) , fileName );
    printf("\n%s", resultFromFile );

    fclose( fileName );

    char str[ 10 ] = "Hello";
    char* copyStr = myStrdup( str );

    if ( copyStr != NULL ) {
        printf("\n%s\n", copyStr );
    }

    char* line_ = NULL;
    size_t size = 0;
    ssize_t res_ = 0;
    res_ = myGetline( &line_, &size, stdin );

    printf("Result of getline: %s %u\n", line_ , size );
    free( line_ );

    return 0;
}
