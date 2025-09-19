#include <TXLib.h>
#include "myStringFunction.h"
#include "parsingText.h"
#include "testStringFunction.h"
#include "preparatoryTask.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main( int argc, char** argv) {
	
    if ( argc > 1 && strcmp( argv[1], "--read" ) == 0) {
        if( !readText() ){
            printf("\nError of open file\n");
        }
        return 0;
    }
    else if( argc > 1 && strcmp( argv[1], "--bufer" ) == 0 ) {
        if ( !workWithBuffer() ){
            printf("\nError with open file and read from him\n");
        }
        return 0;
    }
    else if( argc > 1 && strcmp( argv[1], "--text" ) == 0 ) {
        printText();
    }
	else if ( argc > 1 && strcmp( argv[1], "--test" ) == 0) {
        testMyFunction();
        return 0;
    }

    return 0;
}
