#include "myStringFunction.h"

#include <malloc.h>
#include <assert.h>

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
    assert( line != NULL );
    
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
    assert( line != NULL );
    
    int index = 0;
    
    while ( line[ index++ ] != '\0' );
    
    return index;
}

char* myStrcpy( char* strDestination, const char *strSource ) {
    assert( strDestination != NULL );
    assert( strSource != NULL );
    
    int index = 0;
    
    while( strSource[ index ] != '\0' ) {
        strDestination[ index ] = strSource[ index ];
        ++index;
    }
    
    strDestination[ index ] = '\0';

    return strDestination;
}

char* myStrncpy( char* strDest, const char* strSource, size_t count ) {
    assert( strDest != NULL );
    assert( strSource != NULL );

    size_t index = 0;

    while( index < count && strSource[ index ] != '\0' ) {

        strDest[ index ] = strSource[ index ];
        ++index;
    }

    strDest[ index ] = '\0';

    return strDest;
}

char* myStrcat( char* strDestination, const char* strSource ) {
    assert( strDestination != NULL );
    assert( strSource != NULL );

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
    assert( strDestination != NULL );
    assert( strSource != NULL );

    size_t indexDestination = 0;

    for( ; strDestination[ indexDestination ] != '\0'; indexDestination++ );

    for( size_t indexSource = 0; strSource[ indexSource ] != '\0' && indexSource < count; indexSource++ ) {

        strDestination[ indexDestination ] = strSource[ indexSource ];
        indexDestination++;
    }

    strDestination[ indexDestination ] = '\0';

    return strDestination;

}

int myAtoi( const char* line) {

    if ( line == NULL ) {
        return 0;
    }

    int resultNumber = 0, index = 0;
    while( line[ index ] != '\0' ) {
        
        resultNumber = resultNumber* 10 + ( line[ index ] - '0' );
        ++index;
    }

    return resultNumber;
}

char* myFgets( char* str, int numChars, FILE* stream ) {
    assert( stream != NULL );

    int index = 0, c = '0';

    while ( index < numChars && ( c = fgetc( stream ) ) != EOF && c != '\n' ) {

        str[ index++ ] = c;
    }
    
    if ( c == '\n') str[index++] = '\n';
    str[ index ] = '\0';

    return str;
    
}

char* myStrdup( const char* line ) {
    char* copy = ( char* )calloc( myStrlen( line ) + 1, sizeof( char ) );

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

    const size_t startSize = 32;

    if( line == NULL ) {
        return -1;
    }

    if ( *line == NULL ) {
        char* tryLine =( char* )calloc( startSize, sizeof( char ) );
        
        if ( tryLine == NULL ) {
            return -1;
        }
        *n = startSize;
        *line = tryLine;
    }

    int getChar = 0;
    ssize_t indexCopyLine = 0;

    while( ( getChar = fgetc( stream) ) != '\n' && getChar != EOF ) {

        if ( indexCopyLine == ( *n - 1 ) ) {
            char* tryLine = ( char* )realloc( *line, 2 * (*n) );

            if ( tryLine == NULL ) {
                return -1;
            }
            *line = tryLine;

            ( *n ) *= 2;
        }

        (*line)[ indexCopyLine++  ] = getChar;
    }

    (*line)[ indexCopyLine ] = '\0';
    
    return indexCopyLine;

}