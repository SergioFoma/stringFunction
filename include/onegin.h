#ifndef H_ONEGIN
#define H_ONEGIN

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

struct bufferInformation{
    char* buffer;
    size_t bufferSize;
    size_t fileSize;
};

struct strInformation{
    char** arrayOfStr;
    size_t arraySize;
};

//--------------------------------------------------------------------------------------------------------
//!
//! @return true if reading from the file, allocating memory, and processing the rows were successful, 
//!         otherwise false
//!
//! @brief reads a text file into an array, splits it into lines, sorts it, and writes the result to a file.
//!
//-----------------------------------------------------------------------------------------------------------
bool workWithBuffer( char* nameFileForRead, char* nameFileForWrite);

//------------------------------------------------------------------------------------------------------------
//!
//! @param[in] **arrayOfStr    **arrayOfStr - array of pointers.
//! @param[in] *bufer           *bufer - an array where the entire text file was read.
//! @param[in] fileSize          fileSize - text file size.
//! @param[in] simvol           simvol - the character used for splitting into lines.
//!
//! @brief retrieves the array where the entire text file was read, 
//!        and splits it into lines using the specified character.
//!
//------------------------------------------------------------------------------------------------------------
void getArrayOfStr( strInformation *stringFromFile, bufferInformation *bufferFromText, char simvol );

//-----------------------------------------------------------------------------------------------------------
//!
//! @param[in] *bufer           *bufer - an array where the entire text file was read.
//! @param[in] fileSize          fileSize - text file size.
//! @param[in] simvol           simvol - the character used for splitting into lines.
//!
//! @return count of lines.
//!
//! @brief counts the number of lines in a file.
//!
//-------------------------------------------------------------------------------------------------------------
size_t getSizeStrArray( bufferInformation *bufferFromFile, char simbol );

//-------------------------------------------------------------------------------------------------------------
//!
//! @param[in] **arrayOfStr     **arrayOfStr - array of pointers.
//! @param[in] arrayStrSize     arrayStrSize - count of lines if arrayOfStr.
//!
//! @brief implements bubble sorting by the beginning of rows.
//!
//-------------------------------------------------------------------------------------------------------------
void sortByFirstLetter( strInformation *stringFromFile );

//-------------------------------------------------------------------------------------------------------------
//!
//! @param[in] **arrayOfStr     **arrayOfStr - array of pointers.
//! @param[in] arrayStrSize     arrayStrSize - count of lines if arrayOfStr.
//!
//! @brief implements bubble sorting by the end of rows.
//!
//-------------------------------------------------------------------------------------------------------------
void sortByLastLetter( strInformation *stringFromFile );

//-------------------------------------------------------------------------------------------------------------
//!
//! @param[in] **arrayOfStr     **arrayOfStr - array of pointers.
//! @param[in] arrayStrSize     arrayStrSize - count of lines if arrayOfStr.
//! @param[in] *key             *key - the line that will be printed as the title.
//! @param[in] *mode            *mode - file opening format.
//!
//! @return number of successful operations.
//!
//! @brief prints an array of strings to the output file.
//!
//---------------------------------------------------------------------------------------------------------------
bool printfForFile( char** array, size_t size,char* nameFileForWrite, char* key, const char* mode);

//---------------------------------------------------------------------------------------------------------------
//!
//! @brief gets the size of the text file.
//!
//---------------------------------------------------------------------------------------------------------------
void getFileSize( bufferInformation* bufferFromFile );

//---------------------------------------------------------------------------------------------------------------
//!
//! @param[in] *bufferFromFile      *bufferFromFile - an array in which \n is replaced by \0.
//! @param[in] fileSize             fileSize - size of bufferFromFile.
//!
//! @brief Changes all characters \n to \0 in the limit of the array.
//!
//-------------------------------------------------------------------------------------------------------------
void getOriginalText( bufferInformation *bufferFromFile );

//------------------------------------------------------------------------------------------------------------
//!
//! @param[in] *frist       *first - first const string.
//! @param[in] *second      *second - second const string.
//!
//! @return the value is less than zero if the first row is less than the second, 
//!         zero if the first row is equal to the second row, otherwise positive.
//!
//! @brief compares two strings lexicographically by the beginning.
//!
//--------------------------------------------------------------------------------------------------------------
int sortFirstLetter( const void* first, const void* second );

//------------------------------------------------------------------------------------------------------------
//!
//! @param[in] *frist       *first - first const string.
//! @param[in] *second      *second - second const string.
//!
//! @return the value is less than zero if the first row is less than the second, 
//!         zero if the first row is equal to the second row, otherwise positive.
//!
//! @brief compares two strings lexicographically by the end.
//!
//--------------------------------------------------------------------------------------------------------------
int sortLastLetter( const void* first, const void* second );

//-------------------------------------------------------------------------------------------------------------
//!
//! @param[in] *list    *list - pointer to the array to be sorted.
//! @param[in] count    count - size of array.
//! @param[in] sizeInBytes      sizeInBytes - size elemnt of array in bytes.
//! @param[in] *compare         *compare - function pointer.
//!
//! @brief sorts the array recursively by calling itself.
//!
//----------------------------------------------------------------------------------------------------------------
void myQsort( void* list, size_t count, size_t sizeInBytes, 
              int (*compare)(const void*, const void*) );

bool readFromFile( bufferInformation *bufferFromFile, FILE* myFile );

bool splitToLines( bufferInformation* bufferFromFile, strInformation *stringFromFile, FILE* myFile );

bool sortingRows( strInformation *stringFromFile, char* textForFirstPrint, 
                  char* textForSecondPrint, char* nameFileForOperation, size_t *count, const int key, char* mode,  FILE* myFile);
#endif

