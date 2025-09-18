#include "myStringFunction.h"
#include "testStringFunction.h"

#include <stdlib.h>

void testMyFunction() {
    myPuts( "Hello world" );
	
	char* tryStrchr = myStrchr( "Hello World", 'e' );
	
	if ( tryStrchr == NULL ) printf( "NULL" );
	else printf("%c", *tryStrchr );
	
	printf("\n%u", myStrlen( "Hello, world!" ) );
	
	char copy_line[ 50 ] = "";
	const char line[] = "Hello world from strcpy";
	
	char* tryStrcpy = myStrcpy( copy_line, line );
	printf("\n%s", tryStrcpy );

    char copyLine[ 50 ] = "";
    const char Line[] = "Hello world from strncpy";

    char* tryStrncpy = myStrncpy( copyLine, Line, 10 );
    printf("\n%s", tryStrncpy );

    char firstPart[ 50 ] = "Hello";
    const char secondPart[] = " World from strcat";

    char* tryStrcat = myStrcat( firstPart, secondPart );
    printf("\n%s", tryStrcat );

    char FirstPart[ 50 ] = "Hello";
    const char SecondPart[] = " World from strncat";

    char* tryStrncat = myStrncat( FirstPart, SecondPart, myStrlen( SecondPart ) );
    printf("\n%s", tryStrncat );

    FILE* fileName = fopen( "TestStrFunction.txt", "r");

    if ( fileName == NULL ) {
        printf( "\nОшибка открытия файла" );
    }
    char placeForCopy[50] = "";
    char* tryFgets = myFgets( placeForCopy, sizeof( placeForCopy ) , fileName );
    printf("\n%s", tryFgets );

    fclose( fileName );

    char str[ 10 ] = "Hello";
    char* tryStrdup = myStrdup( str );
    free( str );

    if ( tryStrdup != NULL ) {
        printf("\n%s\n", tryStrdup );
    }

    char* bufer = NULL;
    size_t size = 0;
    ssize_t tryGetline= 0;
    tryGetline = myGetline( &bufer, &size, stdin );

    if ( tryGetline!= -1 ) {
        printf("Result of getline: %s %zd\n", bufer , tryGetline );
    }
    else {
        printf("\nError of open file\n");
    }
    free( bufer );

    const char* myLine = "123";
    int tryAtoi = myAtoi( myLine );
    printf("line 123 like number: %d", tryAtoi );
}