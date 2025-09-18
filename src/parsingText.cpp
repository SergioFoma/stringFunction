#include "parsingText.h"
#include "myStringFunction.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/stat.h>
#include <string.h>
#include <ctype.h>

const int sortByFirst  = 0; // Sort by first letter
const int sortByLast = 1; // Sort by last letter

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

bool workWithBuffer() {
    size_t sizeArrayFromFile = getFileSize();

    printf("Size of file in bayts: %d\n", sizeArrayFromFile );

    char* bufferFromFile = (char*)calloc( sizeArrayFromFile + 1, sizeof( char ) );
    if( bufferFromFile == NULL ){
        printf("\nMemory Error in lines 93\n");
        return false;
    }
    FILE* myFile = fopen("ReadFromText.txt", "r");
    size_t fileSize = fread( bufferFromFile, sizeof( char ), sizeArrayFromFile, myFile );
    bufferFromFile[ sizeArrayFromFile ] = '\0';

    size_t arrayStrSize = getSizeStrArray( bufferFromFile, fileSize, '\n' );
    char** arrayOfStr = (char**)calloc( arrayStrSize, sizeof( char ) );
    if ( arrayOfStr == NULL ){
        printf("\nMemory error in lines 105\n");
        return false;
    }
    printf("Count of str: %u\n", arrayStrSize );
    getArrayOfStr( arrayOfStr, bufferFromFile,  fileSize, '\0' );
    for( size_t strIndex = 0; strIndex < arrayStrSize; strIndex++ ){
        printf("Str[ %u ] = %s\n", strIndex, *(arrayOfStr + strIndex) );
    }
    
    printf("\n\nTEST SORT ¹1\n\n");
    sortByFirstLetter( arrayOfStr, arrayStrSize );
    for( size_t strIndex = 0; strIndex < arrayStrSize; strIndex++ ){
        printf("Line ¹%u stroka by sort: %s\n",strIndex, *(arrayOfStr + strIndex) );
    }

    size_t count = printfForFile( arrayOfStr, arrayStrSize, "\nSorting by the first letter\n\n", "w" );
    if ( count == 0){
        printf("\n\nERROR OF OPEN FILE in line 110\n\n");
        return false;
    }

    printf("\n\nTEST SORT ¹2\n\n");
    sortByLastLetter( arrayOfStr, arrayStrSize );
    for( size_t strIndex = 0; strIndex < arrayStrSize; strIndex++ ){
        printf("Line ¹%u stroka by sort: %s\n",strIndex, *(arrayOfStr + strIndex) );
    }

    count = printfForFile( arrayOfStr, arrayStrSize, "\n\nSorting by the last letter\n\n", "a" );
    if ( count == 0){
        printf("\n\nERROR OF OPEN FILE in line 122\n\n");
        return false;
    }

    getOriginalText( bufferFromFile, fileSize );
    count = printfForFile( &bufferFromFile, 1, "\n\nThe original text\n\n", "a" );
    if ( count == 0){
        printf("\n\nERROR OF OPEN FILE in line 128\n\n");
        return false;
    }

    free( bufferFromFile );
    free( arrayOfStr );
    fclose( myFile );
    return true;
}

// Functions

char* cleanLine( char* lineFromText) {
    assert( lineFromText != NULL);

    size_t index = 0, sizeOfLine = myStrlen( lineFromText );
    while( isalpha( *(lineFromText + index ) ) == 0 ) {
        ++index;
    }
    return lineFromText + index;
}

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

size_t getSizeStrArray( char* buffer, size_t fileSize, char simvol ){
    assert( buffer != NULL );

    size_t sizeArray = 1, sizeBuffer = 0;
    for( ; sizeBuffer < fileSize; sizeBuffer++){
        if ( *( buffer + sizeBuffer ) == simvol ){
            *(buffer + sizeBuffer) = '\0';
            ++sizeArray;
        }
    }
    return sizeArray;
}
void getArrayOfStr( char** arrayOfStr, char* buffer, size_t fileSize, char simvol ) {
    assert( arrayOfStr != NULL );
    assert( buffer );

    size_t bufferIndex = 0, arrayStrIndex = 1;
    *arrayOfStr = cleanLine( buffer );
    for( ; bufferIndex < fileSize; bufferIndex++ ){
        if ( *( buffer + bufferIndex ) == simvol ) {
            *( arrayOfStr + arrayStrIndex ) = cleanLine( ( buffer + bufferIndex + 1) );
            ++arrayStrIndex;
        }
    }
}

void sortByFirstLetter( char** arrayOfStr, size_t arrayStrSize ){
    assert( arrayOfStr != NULL );
    assert( (*arrayOfStr) != NULL );

    char* tmp = "\0";
    for( size_t firstStep = 0; firstStep < arrayStrSize; firstStep++ ){
        for( size_t secondStep = 0; secondStep < arrayStrSize - 1; secondStep++ ){
            if ( myStrcmp( *( arrayOfStr + secondStep ) , *( arrayOfStr + secondStep + 1), sortByFirst ) > 0 ){
                tmp = *( arrayOfStr + secondStep );
                *( arrayOfStr + secondStep ) = *( arrayOfStr + secondStep + 1);
                *( arrayOfStr + secondStep + 1) = tmp;
            }
        }
    }

}

void sortByLastLetter( char** arrayOfStr, size_t arrayStrSize ){
    assert( arrayOfStr != NULL );
    assert( (*arrayOfStr) != NULL );

    char* tmp = "\0";
    for( size_t firstStep = 0; firstStep < arrayStrSize; firstStep++ ){
        for( size_t secondStep = 0; secondStep < arrayStrSize - 1; secondStep++ ){
            if ( myStrcmp( *( arrayOfStr + secondStep ) , *( arrayOfStr + secondStep + 1), sortByLast ) > 0 ){
                tmp = *( arrayOfStr + secondStep );
                *( arrayOfStr + secondStep ) = *( arrayOfStr + secondStep + 1);
                *( arrayOfStr + secondStep + 1) = tmp;
            }
        }
    }

}

size_t getFileSize(){
    struct stat fileText;
    int status = stat("ReadFromText.txt", &fileText );
    
    printf("Status of reading: %d\n", status );

    return fileText.st_size;
}

size_t printfForFile( char** arrayOfStr, size_t arrayStrSize, char* key, const char* mode ){
    assert( arrayOfStr != NULL );
    assert( (*arrayOfStr) != NULL );
    assert( key != NULL );
    assert( mode != NULL );

    FILE* printFile = fopen("CorrectPoem.txt", mode);
    fputs(key, printFile);
    for( size_t index = 0; index < arrayStrSize; index++){
        if ( fputs( *(arrayOfStr+index), printFile) == EOF ){
            printf("\nError of open file to print in line 239\n");
            return 0;
        }
        if( fputc( '\n', printFile ) == EOF ){
            printf("\nError of open file to print in line 243\n");
            return 0;
        }
    }
    fclose( printFile );
    return 1;
}

void getOriginalText( char* bufferFromFile, size_t fileSize ){
    assert( bufferFromFile != NULL );

    for( size_t index = 0; index < fileSize; index++ ){
        if( *(bufferFromFile + index) == '\0' ){
            *(bufferFromFile + index ) = '\n';
        }
    }

    *(bufferFromFile + fileSize ) = '\0';
}
