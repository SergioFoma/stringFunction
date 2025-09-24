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
    getFileSize( &bufferFromFile );
    size_t fileSize          = 0;
    size_t arrayStrSize      = 0;
    size_t count             = 0;

    colorPrintf(NOMODE, YELLOW, "Size of file in bytes: %d\n", bufferFromFile.bufferSize );

    FILE* myFile = fopen( nameFileForRead, "r");
    readFromFile( bufferFromFile, &fileSize, myFile );
    
    char** arrayOfStr = splitToLines( bufferFromFile, &arrayStrSize, fileSize, myFile );
    
    if (!sortingRows( arrayOfStr, arrayStrSize, "\n\nTEST SORT ¹1\n\n", "\nSorting by the first letter\n\n",
                      nameFileForWrite, &count, sortByFirst, "w", myFile) ){
        return false;
    }

    if (!sortingRows( arrayOfStr, arrayStrSize, "\n\nTEST SORT ¹2\n\n",  "\nSorting by the second letter\n\n",
                      nameFileForWrite, &count, sortByLast,"a", myFile) ){
        return false;
    }

    getOriginalText( bufferFromFile, fileSize );
    count = printfForFile( &bufferFromFile, 1, nameFileForWrite, "\n\nThe original text\n\n", "a" );
    if ( count == 0){
        printfError("\n\nERROR OF OPEN FILE\n\n");
        fclose( myFile );
        return false;
    }

    free( bufferFromFile );
    free( arrayOfStr );
    fclose( myFile );
    return true;
}

// Functions
bool readFromFile( bufferInformation *bufferFromFile, size_t *fileSize, FILE* myFile){
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
    (*fileSize) = fread( bufferFromFile->buffer, sizeof( char ), bufferFromFile->bufferSize, myFile );
    if( fileSize == 0 ){
        printfError("\n\nError of read text from file to bufer\n\n");
    }
    (bufferFromFile->buffer)[ bufferFromFile->bufferSize ]= '\0';
    (bufferFromFile->buffer)[ (*fileSize) ] = '\0';

    return true;
}

char** splitToLines( char* bufferFromFile, size_t *arrayStrSize, size_t fileSize, FILE* myFile ){
    (*arrayStrSize) = getSizeStrArray( bufferFromFile, fileSize, '\n' );
    char** arrayOfStr = (char**)calloc( (*arrayStrSize), sizeof( char* ) );
    if ( arrayOfStr == NULL ){
        printfError("\n\nMemory error\n\n");
        fclose( myFile );
        return false;
    }
    colorPrintf(NOMODE, YELLOW, "Count of str: %u\n", (*arrayStrSize) );
    getArrayOfStr( arrayOfStr, bufferFromFile,  fileSize, '\0' );

    return arrayOfStr;
}

bool sortingRows( char** arrayOfStr, size_t arrayStrSize, char* textForFirstPrint, char* textForSecondPrint,
                 char* nameFileForOperation,size_t *count,const int key, char* mode, FILE* myFile){

    colorPrintf(NOMODE, GREEN, textForFirstPrint);
    if ( key == sortByFirst){
        myQsort( arrayOfStr, arrayStrSize, sizeof( char*), sortFirstLetter );
    }
    else{
        myQsort( arrayOfStr, arrayStrSize, sizeof( char*), sortLastLetter );
    }
    (*count)= printfForFile( arrayOfStr, arrayStrSize, nameFileForOperation, textForSecondPrint, mode );
    if ( (*count) == 0){
        printfError("\n\nERROR OF OPEN FILE\n\n");
        fclose( myFile );
        return false;
    }

    return true;
}

size_t getSizeStrArray( char* buffer, size_t fileSize, char simbol ){
    assert( buffer != NULL );

    size_t arraySize = 1, sizeBuffer = 0;
    for( ; sizeBuffer < fileSize; sizeBuffer++){
        if ( *( buffer + sizeBuffer ) == simbol ){
            *(buffer + sizeBuffer) = '\0';
            ++arraySize;
        }
    }
    return arraySize;
}
void getArrayOfStr( char** arrayOfStr, char* buffer, size_t fileSize, char simvol ) {
    assert( arrayOfStr != NULL );
    assert( buffer != NULL );

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

void getFileSize( bufferInformation* bufferFromFile ){
    struct stat fileText;
    int status = stat("ReadFromText.txt", &fileText );
    
    colorPrintf(NOMODE, YELLOW, "Status of reading: %d\n", status );
    bufferFromFile->bufferSize = fileText.st_size;
}

size_t printfForFile( char** arrayOfStr, size_t arrayStrSize,char* nameFileForWrite, char* key, const char* mode ){
    assert( arrayOfStr != NULL );
    assert( (*arrayOfStr) != NULL );
    assert( key != NULL );
    assert( mode != NULL );

    FILE* printFile = fopen( nameFileForWrite, mode);
    if ( printFile == NULL ){
        printfError("\nNULL PTR\n");
        fclose( printFile );
        return 0;
    }
    if ( fputs(key, printFile) == EOF ){
        printfError("\n%s Error to write a key\n");
        fclose( printFile );
        return 0;
    }
    for( size_t index = 0; index < arrayStrSize; index++){
        if ( myStrlen( *(arrayOfStr + index ) ) > 0 && fputs( *(arrayOfStr+index), printFile) == EOF ){
            printfError("\nError of open file and wrint in him\n");
            fclose( printFile );
            return 0;
        }
        if( fputc( '\n', printFile ) == EOF ){
            printfError("\nError of open file and write in him\n");
            fclose( printFile );
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
