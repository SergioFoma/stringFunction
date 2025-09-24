#include "onegin.h"
#include "myStringFunction.h"
#include "preparatoryTask.h"
#include "paint.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/stat.h>
#include <string.h>
#include <ctype.h>

const int sortByFirst  = 0; // Sort by first letter
const int sortByLast = 1; // Sort by last letter

bool workWithBuffer( char* nameFileForRead, char* nameFileForWrite) {
    bufferInformation bufferFromFile = {};
    strInformation stringFromFile = {};

    getFileSize( &bufferFromFile );
    size_t count             = 0;

    colorPrintf(NOMODE, YELLOW, "Size of file in bytes: %d\n", bufferFromFile.bufferSize );

    FILE* myFile = fopen( nameFileForRead, "r");
    if ( !readFromFile( &bufferFromFile, myFile ) ){
        return false;
    }
    
    if ( !splitToLines( &bufferFromFile, &stringFromFile, myFile ) ){
        return false;
    }
    
    if (!sortingRows( &stringFromFile, "\n\nTEST SORT ¹1\n\n", "\nSorting by the first letter\n\n",
                      nameFileForWrite, &count, sortByFirst, "w", myFile) ){
        return false;
    }

    if (!sortingRows( &stringFromFile, "\n\nTEST SORT ¹2\n\n",  "\nSorting by the second letter\n\n",
                      nameFileForWrite, &count, sortByLast,"a", myFile) ){
        return false;
    }

    getOriginalText( &bufferFromFile );
    if ( !printfForFile( &(bufferFromFile.buffer), 1, nameFileForWrite, "\n\nThe original text\n\n", "a" ) ) {
        printfError("\n\nERROR OF OPEN FILE\n\n");
        fclose( myFile );
        return false;
    }

    free( bufferFromFile.buffer );
    free( stringFromFile.arrayOfStr );
    fclose( myFile );
    return true;
}

// Functions
bool readFromFile( bufferInformation *bufferFromFile, FILE* myFile){
    assert( bufferFromFile != NULL );

    if( myFile == NULL ){
        printfError("\n\nNULL ptr\n\n");
        fclose( myFile );
        return false;
    }
    bufferFromFile->buffer = (char*)calloc( bufferFromFile->bufferSize + 1, sizeof( char ) );
    if( bufferFromFile->buffer == NULL ){
         printfError("\n\nMemory Error\n\n");
        return false;
    }
    bufferFromFile->fileSize = fread( bufferFromFile->buffer, sizeof( char ), bufferFromFile->bufferSize, myFile );
    if( bufferFromFile->fileSize == 0 ){
        printfError("\n\nError of read text from file to bufer\n\n");
    }
    (bufferFromFile->buffer)[ bufferFromFile->bufferSize ]= '\0';
    (bufferFromFile->buffer)[ bufferFromFile->fileSize ] = '\0';

    return true;
}

bool splitToLines( bufferInformation *bufferFromFile, strInformation *stringFromFile, FILE* myFile ){
    assert( bufferFromFile != NULL );
    assert( stringFromFile != NULL );
    assert( myFile != NULL );

    stringFromFile->arraySize = getSizeStrArray( bufferFromFile, '\n' );
    (stringFromFile->arrayOfStr) = (char**)calloc( stringFromFile->arraySize, sizeof( char* ) );
    if ( (stringFromFile->arrayOfStr) == NULL ){
        printfError("\n\nMemory error\n\n");
        fclose( myFile );
        return false;
    }
    colorPrintf(NOMODE, YELLOW, "Count of str: %u\n", stringFromFile->arraySize );
    getArrayOfStr( stringFromFile, bufferFromFile, '\0' );

    return true;
}

bool sortingRows( strInformation *stringFromFile, char* textForFirstPrint, char* textForSecondPrint,
                 char* nameFileForOperation, size_t *count, const int key, char* mode, FILE* myFile){
    assert( stringFromFile != NULL );
    assert( textForFirstPrint != NULL );
    assert( textForFirstPrint != NULL );
    assert( nameFileForOperation != NULL );
    assert( count != NULL );
    assert( myFile != NULL );

    colorPrintf(NOMODE, GREEN, textForFirstPrint);
    if ( key == sortByFirst){
        myQsort( (stringFromFile->arrayOfStr), (stringFromFile->arraySize), sizeof( char*), sortFirstLetter );
    }
    else{
        myQsort( (stringFromFile->arrayOfStr), (stringFromFile->arraySize), sizeof( char*), sortLastLetter );
    }
    (*count)= printfForFile( stringFromFile->arrayOfStr, stringFromFile->arraySize, nameFileForOperation, textForSecondPrint, mode );
    if ( (*count) == 0){
        printfError("\n\nERROR OF OPEN FILE\n\n");
        fclose( myFile );
        return false;
    }

    return true;
}

size_t getSizeStrArray( bufferInformation *bufferFromFile, char simbol ){
    assert( bufferFromFile != NULL );

    size_t arraySize = 1, sizeBuffer = 0;
    for( ; sizeBuffer < (bufferFromFile->fileSize); sizeBuffer++){
        if ( (bufferFromFile->buffer)[sizeBuffer] == simbol ){
            (bufferFromFile->buffer)[sizeBuffer] = '\0';
            ++arraySize;
        }
    }
    return arraySize;
}
void getArrayOfStr( strInformation *stringFromFile, bufferInformation *bufferFromFile, char simvol ) {
    assert( stringFromFile != NULL );
    assert( bufferFromFile != NULL );

    size_t bufferIndex = 0, arrayStrIndex = 1;
    (stringFromFile->arrayOfStr)[0] = cleanLine( (bufferFromFile->buffer) );
    for( ; bufferIndex < (bufferFromFile->fileSize); bufferIndex++ ){
        if ( (bufferFromFile->buffer)[bufferIndex] == simvol ) {
            (stringFromFile->arrayOfStr)[arrayStrIndex] = cleanLine( ( (bufferFromFile->buffer) + bufferIndex + 1) );
            ++arrayStrIndex;
        }
    }
}

void sortByFirstLetter( strInformation *stringFromFile ){
    assert( stringFromFile != NULL );

    char* tmp = "\0";
    for( size_t firstStep = 0; firstStep < (stringFromFile->arraySize); firstStep++ ){
        for( size_t secondStep = 0; secondStep < (stringFromFile->arraySize) - 1; secondStep++ ){
            if ( myStrcmp((stringFromFile->arrayOfStr)[secondStep] , (stringFromFile->arrayOfStr)[secondStep+1], sortByFirst ) > 0 ){
                tmp = (stringFromFile->arrayOfStr)[secondStep];
                (stringFromFile->arrayOfStr)[secondStep] = (stringFromFile->arrayOfStr)[secondStep+1];
                (stringFromFile->arrayOfStr)[secondStep+1] = tmp;
            }
        }
    }

}

void sortByLastLetter( strInformation *stringFromFile ){
    assert( stringFromFile != NULL );

    char* tmp = "\0";
    for( size_t firstStep = 0; firstStep < (stringFromFile->arraySize); firstStep++ ){
        for( size_t secondStep = 0; secondStep < (stringFromFile->arraySize) - 1; secondStep++ ){
            if ( myStrcmp( (stringFromFile->arrayOfStr)[secondStep] , (stringFromFile->arrayOfStr)[secondStep+1], sortByLast ) > 0 ){
                tmp = (stringFromFile->arrayOfStr)[secondStep];
                (stringFromFile->arrayOfStr)[secondStep] = (stringFromFile->arrayOfStr)[secondStep+1];
                (stringFromFile->arrayOfStr)[secondStep+1] = tmp;
            }
        }
    }

}

void getFileSize( bufferInformation* bufferFromFile ){
    assert( bufferFromFile != NULL );

    struct stat fileText;
    int status = stat("ReadFromText.txt", &fileText );
    
    colorPrintf(NOMODE, YELLOW, "Status of reading: %d\n", status );
    bufferFromFile->bufferSize = fileText.st_size;
}

bool printfForFile( char** arrayOfStr, size_t arrayStrSize,char* nameFileForWrite, char* key, const char* mode ){
    assert( arrayOfStr != NULL );
    assert( key != NULL );
    assert( mode != NULL );

    FILE* printFile = fopen( nameFileForWrite, mode);
    if ( printFile == NULL ){
        printfError("\nNULL PTR\n");
        fclose( printFile );
        return false;
    }
    if ( fputs(key, printFile) == EOF ){
        printfError("\n%s Error to write a key\n");
        fclose( printFile );
        return false;
    }
    for( size_t index = 0; index < arrayStrSize; index++){
        if ( myStrlen( *(arrayOfStr + index ) ) > 0 && fputs( *(arrayOfStr+index), printFile) == EOF ){
            printfError("\nError of open file and wrint in him\n");
            fclose( printFile );
            return false;
        }
        if( fputc( '\n', printFile ) == EOF ){
            printfError("\nError of open file and write in him\n");
            fclose( printFile );
            return false;
        }
    }
    fclose( printFile );
    return true;
}

void getOriginalText( bufferInformation *bufferFromFile ){
    assert( bufferFromFile != NULL );

    for( size_t index = 0; index < (bufferFromFile->fileSize); index++ ){
        if( (bufferFromFile->buffer)[index] == '\0' ){
            (bufferFromFile->buffer)[index] = '\n';
        }
    }

    (bufferFromFile->buffer)[ (bufferFromFile->fileSize)] = '\0';
}

int sortFirstLetter( const void* first, const void* second ){
    assert( first != NULL );
    assert( second != NULL );
    return myStrcmp( *(const char**)first, *(const char**)second, sortByFirst );
}

int sortLastLetter( const void* first, const void* second ){
    assert( first != NULL );
    assert( second != NULL );
    return myStrcmp( *(const char**)first, *(const char**)second, sortByLast );
}

void myQsort( void* list, size_t count, size_t sizeInBytes, 
              int (*compare)(const void*, const void*) ){
                assert( list != NULL );
                assert( compare != NULL );

                if( count  < 2){
                    return ;
                }

                size_t baseIndex = 0,  indexMaxEl = count - 1, i = 0;
                for( size_t j = baseIndex; j < indexMaxEl; j++){

                    if( compare( (char**)list + j, (char**)list + indexMaxEl) <= 0 ){
                        changeLine( (char**)list + i, (char**)list + j );
                        ++i;
                    }
                }
                changeLine( (char**)list + i, (char**)list + indexMaxEl );

                myQsort( (char**)list, i , sizeInBytes, compare );
                myQsort( (char**)list + i  , count - i , sizeInBytes, compare);
}
