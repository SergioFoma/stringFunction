#ifndef H_PREPARATORYTASK
#define H_PREPARATORYTASK

#include <stdlib.h>

//------------------------------------------------------------------------------------
//!
//! @return 1 if reading from the file to the string array was successful, otherwise 0.
//!
//! @brief reads lines from a file into an array of pointers. Prints the result.
//!
//-------------------------------------------------------------------------------------
bool readText();

//-----------------------------------------------------------------------------------------------------
//!
//! @brief reads lines from a file into a two-dimensional array and displays the result on the console.
//!
//-----------------------------------------------------------------------------------------------------
void printText();

//-----------------------------------------------------------------------------------------------------
//!
//! @param[in] **firstLine      **firstLine - pointer to the first line.
//! @param[in] **secondLine     **secondLine - pointer to the second line.
//!
//! @brief swaps to lines.
//!
//-----------------------------------------------------------------------------------------------------
void swap( void* firstLine, void* secondLine, size_t sizeInBytes);

//----------------------------------------------------------------------------------------------------
//!
//! @param[in] *line_1      *line_1 - the first line.
//! @param[in] *line_2      *line_2 - the second line.
//! @param[in] Size         size - size of lines.
//!
//! @brief changes two lines character by character.
//!
//----------------------------------------------------------------------------------------------------
void doSwap( char* line_1, char* line_2, const size_t Size );
#endif