#include "preparatoryTask.h"
#include "myStringFunction.h"
#include "paint.h"

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
            colorPrintf(NOMODE, RED,"\nmemory allocation error.\n");
            return false;
        }
        
        text[ numberLine ] = lineFromText;
    }

    //changeLine( text + 0, text + 1, sizeof( char) ); // Change str - just fun

    for( size_t index = 0; index < countLine; index++ ){
        colorPrintf(NOMODE, GREEN, "%d %s", myStrlen( *(text+index) ), *(text+index) );
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
        colorPrintf(NOMODE, GREEN, "%s", text[ line ] );
    }

    fclose( File );
}

// Functions

void swap( void* firstLine, void* secondLine, size_t sizeInBytes ) {
    assert( firstLine != NULL );
    assert( secondLine != NULL );

    for( size_t index = 0; index < sizeInBytes; index++ ){
        char tmp = *((char*)firstLine + index );
        *((char*)firstLine + index) = *((char*)secondLine + index);
        *((char*)secondLine + index) = tmp;
    }
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