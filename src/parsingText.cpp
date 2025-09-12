#include "parsingText.h"
#include "myStringFunction.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

char* cleanLine( char* lineFromText) {
    assert( lineFromText );
    int index = 0;
    while( *( lineFromText+ index ) == ' ') {
        index++;
    }
    return lineFromText + index;
}

void changeLine( char** firstLine, char** secondLine) {
    assert( firstLine );
    assert( secondLine );

    char* tmp = (*firstLine);
    (*firstLine) = (*secondLine);
    (*secondLine) = tmp;
}
bool ReadText() {

    const size_t countLine = 5;
    const size_t maxLen = 30;

    char* text[5] = {};
    FILE* file = fopen("ReadFromText.txt", "r");

    if ( file == NULL ) {
        return false;
    }

    char line[ maxLen ] = "\0";
    for ( size_t numberLine = 0; numberLine < countLine; numberLine++ ){
        myFgets( line, maxLen, file);
        char* lineFromText = myStrdup( line );

        if ( lineFromText == NULL ) {
            printf("\nmemory allocation error.\n");
            return false;
        }
        
        lineFromText = cleanLine( lineFromText );
        text[ numberLine ] = lineFromText;
    }

    //changeLine( text + 0, text + 1 );

    for( size_t index = 0; index < countLine; index++ ){
        printf("%s", *(text+index) );
        free( *(text+ index) );
    }

    return true;

}
