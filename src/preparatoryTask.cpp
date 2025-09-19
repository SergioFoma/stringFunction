#include "preparatoryTask.h"
#include "myStringFunction.h"

#include <assert.h>
// Decosion dy array with char*
bool readText() {

    const size_t countLine = 5;
    const size_t maxLen = 50;

    char* text[ countLine ] = {};
    FILE* file = fopen("ReadFromText.txt", "r");

    if ( file == NULL ) {
        return false;
    }

    char line[ maxLen ] = "\0";
    for ( size_t numberLine = 0; numberLine < countLine; numberLine++ ){
        myFgets( line, maxLen, file);
        char* correctLine = cleanLine( line );
        char* lineFromText = myStrdup( correctLine );

        if ( lineFromText == NULL ) {
            printf("\nmemory allocation error.\n");
            return false;
        }
        
        text[ numberLine ] = lineFromText;
    }

    changeLine( text + 0, text + 1 ); // Change str - just fun

    for( size_t index = 0; index < countLine; index++ ){
        printf("%d %s", myStrlen( *(text+index) ), *(text+index) );
        free( *(text+ index) );
    }

    fclose( file );

    return true;
}

// Decision by matrix
void printText() {
    const size_t maxLen = 50;
    const size_t count = 5;

    char text[ count ][ maxLen ] = { };
    FILE* File = fopen("ReadFromText.txt", "r");

    for ( size_t line = 0; line < count; line++ ) {
        myFgets( text[ line ], maxLen, File );
    }

    doSwap( text[0], text[1] , maxLen );

    for ( size_t line = 0; line < count; line++ ) {
        printf("%s", text[ line ] );
    }

    fclose( File );
}

// Functions

void changeLine( char** firstLine, char** secondLine) {
    assert( firstLine != NULL );
    assert( (*firstLine) != NULL );
    assert( secondLine != NULL );
    assert( (*secondLine) != NULL );

    char* tmp = (*firstLine);
    (*firstLine) = (*secondLine);
    (*secondLine) = tmp;
}

void doSwap( char* line_1, char* line_2, const size_t Size ) {
    assert( line_1 != NULL );
    assert( line_2 != NULL );
    
    size_t index = 0;

    while( index < Size ) {
        char tmp = *(line_1 + index );
        *(line_1 + index ) = *(line_2 + index );
        *(line_2 + index ) = tmp;
        ++index;
    }
}