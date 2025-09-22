#include <TXLib.h>
#include "myStringFunction.h"
#include "onegin.h"
#include "testStringFunction.h"
#include "preparatoryTask.h"
#include "paint.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main( int argc, char** argv) {
    if ( argc > 1 && strcmp( argv[1], "--read" ) == 0) {
        if( !readText() ){
            colorPrintf(NOMODE, RED,"\nError of open file %d %s\n", __LINE__, __func__);
        }
        return 0;
    }
    else if( argc > 1 && strcmp( argv[1], "--onegin" ) == 0 ) {
        if ( !workWithBuffer() ){
            printf("\nError with open file and read from him %d %s\n", __LINE__, __func__);
        }
        return 0;
    }
    else if( argc > 1 && strcmp( argv[1], "--text" ) == 0 ) {
        printText();
        return 0;
    }
	else if ( argc > 1 && strcmp( argv[1], "--test" ) == 0) {
        testMyFunction();
        return 0;
    }

    return 0;
}
