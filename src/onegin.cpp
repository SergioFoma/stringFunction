#include "onegin.h"
#include "myStringFunction.h"
#include "preparatoryTask.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/stat.h>
#include <string.h>
#include <ctype.h>

const int sortByFirst  = 0; // Sort by first letter
const int sortByLast = 1; // Sort by last letter

bool workWithBuffer() {
    size_t sizeArrayFromFile = getFileSize();

    printf("Size of file in bytes: %d\n", sizeArrayFromFile );

    char* bufferFromFile = (char*)calloc( sizeArrayFromFile + 1, sizeof( char ) );
    if( bufferFromFile == NULL ){
        printf("\n\nMemory Error in line %d %s\n\n", __LINE__, __func__ );
        return false;
    }
    FILE* myFile = fopen("ReadFromText.txt", "r");
    if( myFile == NULL ){
        printf("\n\nNULL ptr %d %s\n\n", __LINE__, __func__);
        fclose( myFile );
        return false;
    }
    size_t fileSize = fread( bufferFromFile, sizeof( char ), sizeArrayFromFile, myFile );
    if( fileSize == 0 ){
        printf("\n\nError of read text from file to bufer %d %s\n\n", __LINE__, __func__);
    }
    bufferFromFile[ sizeArrayFromFile ] = '\0';
    bufferFromFile[ fileSize ] = '\0';

    size_t arrayStrSize = getSizeStrArray( bufferFromFile, fileSize, '\n' );
    char** arrayOfStr = (char**)calloc( arrayStrSize, sizeof( char* ) );
    if ( arrayOfStr == NULL ){
        printf("\n\nMemory error in line %d %s\n\n", __LINE__, __func__ );
        fclose( myFile );
        return false;
    }
    printf("Count of str: %u\n", arrayStrSize );
    getArrayOfStr( arrayOfStr, bufferFromFile,  fileSize, '\0' );
    
    printf("\n\nTEST SORT ¹1\n\n");
    myQsort( arrayOfStr, arrayStrSize, sizeof( char*), sortFirstLetter );
    size_t count = printfForFile( arrayOfStr, arrayStrSize, "\nSorting by the first letter\n\n", "w" );
    if ( count == 0){
        printf("\n\nERROR OF OPEN FILE in line %d %s\n\n", __LINE__, __func__);
        fclose( myFile );
        return false;
    }

    printf("\n\nTEST SORT ¹2\n\n");
    myQsort( arrayOfStr, arrayStrSize, sizeof( char*), sortLastLetter );
    count = printfForFile( arrayOfStr, arrayStrSize, "\n\nSorting by the last letter\n\n", "a" );
    if ( count == 0){
        printf("\n\nERROR OF OPEN FILE in line %d %s\n\n", __LINE__, __func__);
        fclose( myFile );
        return false;
    }

    getOriginalText( bufferFromFile, fileSize );
    count = printfForFile( &bufferFromFile, 1, "\n\nThe original text\n\n", "a" );
    if ( count == 0){
        printf("\n\nERROR OF OPEN FILE in line %d %s\n\n", __LINE__, __func__ );
        fclose( myFile );
        return false;
    }

    free( bufferFromFile );
    free( arrayOfStr );
    fclose( myFile );
    return true;
}

// Functions

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
    if ( printFile == NULL ){
        printf("\nmode = %s nNull ptr %d %s\n",mode,  __LINE__, __func__ );
        fclose( printFile );
        return 0;
    }
    if ( fputs(key, printFile) == EOF ){
        printf("\n%s Error to write a key %d %s\n", mode,  __LINE__, __func__ );
        fclose( printFile );
        return 0;
    }
    for( size_t index = 0; index < arrayStrSize; index++){
        if ( myStrlen( *(arrayOfStr + index ) ) > 0 && fputs( *(arrayOfStr+index), printFile) == EOF ){
            printf("\nError of open file to print in line %d %s\n",__LINE__, __func__);
            fclose( printFile );
            return 0;
        }
        if( fputc( '\n', printFile ) == EOF ){
            printf("\nError of open file to print in line %d %s\n", __LINE__, __func__);
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
