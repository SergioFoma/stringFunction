#include "allFunction.h"

#include <malloc.h>

int myPuts( const char* line ) {
    
    if ( line == NULL ) {
        return EOF;
    }
    
    int index = 0;
    
    while ( line[ index ] != '\0' ) {
        
        putchar( line[ index++ ] );
    }
    
    putchar('\n');
    return 1;
}

char* myStrchr( const char* line, int ch ) {
    
    int index = 0;
    
    while( line[ index ] != '\0' ) {
        
        if ( line[ index ] == ch ) {
            
            return (char*)( &(line[ index ]) ) ;
        }
        
        ++index;
    }
    
    if ( line[ index ] == '\0' ) {
        return NULL;
    }
}


size_t myStrlen( const char* line ) {
    
    int index = 0;
    
    while ( line[ index ] != '\0' ) {
        
        ++index;
    }
    
    return index;
}

char* myStrcpy( char* strDestination, const char *strSource ) {
    
    int index = 0;
    
    while( strSource[ index ] != '\0' ) {
        strDestination[ index ] = strSource[ index ];
        ++index;
    }
    
    strDestination[ index ] != '\0';

    return strDestination;
}

char* myStrncpy( char* strDest, const char* strSource, size_t count ) {

    int index = 0;

    while( index < count && strSource[ index ] != '\0' ) {

        strDest[ index ] = strSource[ index ];
        ++index;
    }

    strDest[ index ] = '\0';

    return strDest;
}

char* myStrcat( char* strDestination, const char* strSource ) {

    int indexDestination = 0;

    for( ; strDestination[ indexDestination ] != '\0'; indexDestination++ );

    for( int indexSource = 0; strSource[ indexSource ] != '\0'; indexSource++ ) {

        strDestination[ indexDestination ] = strSource[ indexSource ];
        ++indexDestination;
    }

    strDestination[ indexDestination ] = '\0';

    return strDestination;
}

char* myStrncat( char* strDestination, const char* strSource, size_t count ) {

    int indexDestination = 0;

    for( ; strDestination[ indexDestination ] != '\0'; indexDestination++ );

    for( int indexSource = 0; strSource[ indexSource ] != '\0' && indexSource < count; indexSource++ ) {

        strDestination[ indexDestination ] = strSource[ indexSource ];
        indexDestination++;
    }

    strDestination[ indexDestination ] = '\0';

    return strDestination;

}

char* myFgets( char* str, int numChars, FILE* stream ) {

    int index = 0, c = '0';

    while ( index < numChars && ( c = fgetc( stream ) ) != EOF ) {

        str[ index++ ] = c;
    }

    str[ index ] = '\0';

    return str;
    
}

char* myStrdup( const char* line ) {

    char* copy = ( char* )calloc( myStrlen( line ), sizeof( char ) );

    if ( copy == NULL ) {
        return NULL;
    }

    int index = 0;

    while( line[ index ] != '\0' ) {
        copy[ index ] = line[ index ];
        ++index;
    }

    copy[ index ] = line[ index ];

    return copy;
}

ssize_t myGetline( char** line, size_t* n, FILE* stream ) {

    if ( line == NULL ) {
        return -1;
    }

    const size_t startSize = 32;

    if ( *line == NULL ) {

        *line = ( char* )calloc( startSize , sizeof( char ) );
        *n = startSize;
    }

    int getChar = '0';
    ssize_t index = 0;

    while( ( getChar = fgetc( stream ) ) != '\n') {

        if ( index  == ( *n - 1 ) ) {

            char* tryAllocateMemory = ( char* )realloc( *line, *n * 2);

            if ( tryAllocateMemory == NULL ) {
                return -1;
            }
            else {
                *line = tryAllocateMemory;
            }
            *n *= 2;
        }

        (*line)[ index++ ] = getChar;
    }

    ((*line)[ index ]) = '\0';

    return index;
}