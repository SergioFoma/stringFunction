#ifndef H_MYSTRINGFUNCTION
#define H_MYSTRINGFUNCTION

#include <stdio.h>
#include <unistd.h>

//-----------------------------------------------
//!
//! @param[in] line     line - const string.
//!
//! @brief prints a line to the console.
//!
//------------------------------------------------
int myPuts( const char* line );

//--------------------------------------------------------------------------
//!
//! @param[in] line     line - const string.
//! @param[in] ch       ch - a symbol that is searched for in the line.
//!
//! @return a non-negative value if successful, otherwise EOF.
//!
//! @brief Searches for the first occurrence of the character ch in the line.
//!
//----------------------------------------------------------------------------
char* myStrchr( const char* line, int ch );

//----------------------------------------------------------------------------
//!
//! @param[in] line     line - const string.
//!
//! @return the length of the line line.
//!
//! @brief Searches for the length of a constant string line.
//!
//-----------------------------------------------------------------------------
size_t myStrlen( const char* line );

//-----------------------------------------------------------------------------------
//!
//! @param[in] strDestination   strDestination - the line where the copy is being made.
//! @param[in] strSource        strSource - the constant string that is being copied.
//!
//! @return the string that was copied ( strDestination ).
//!
//! @brief Copies one line to another.
//!
//-----------------------------------------------------------------------------------
char* myStrcpy( char* strDestination, const char *strSource );

//------------------------------------------------------------------------------------
//!
//! @param[in] strDest      strDest - the line that is being copied to.
//! @param[in] strSource    strSource - the constant string that is being copied.
//! @param[in] count        count - the number of characters to copy.
//!
//! @return the string that was copied ( strDest ).
//!
//! @brief copies the specified number of characters from one line to another.
//!
//-------------------------------------------------------------------------------------
char* myStrncpy( char *strDest, const char *strSource, size_t count );

//-------------------------------------------------------------------------------------------------
//!
//! @param[in] strDestination   strDestination - a string to which another string will be added.
//! @param[in] strSource        strSource - a string that will be added to another string.
//!
//! @return a string with another string added to the end.
//!
//! @brief Adds one line to the end of another.
//!
//---------------------------------------------------------------------------------------------------
char* myStrcat( char* strDestination, const char* strSource );

//---------------------------------------------------------------------------------------------------
//!
//! @param[in] strDestination   strDestination - a string to which another string will be added.
//! @param[in] strSource        strSource - a string that will be added to another string.
//! @param[in] count            count - the number of characters to add.
//!
//! @return a string with characters added to the end of another string.
//!
//! @brief Adds the specified number of characters from one line to the end of another.
//!
//---------------------------------------------------------------------------------------------------
char* myStrncat( char* strDestination, const char* strSource, size_t count );

//----------------------------------------------------------------------------------------------------
//!
//! @param[in] line     line - a constant string representing a number.
//!
//! @return an integer obtained from a string.
//!
//! @brief Converts an integer from string format to numeric format.
//!
//-----------------------------------------------------------------------------------------------------
int myAtoi( const char* line );

//---------------------------------------------------------------------------------------------------
//!
//! @param[in] str          str - a string where characters from the file will be written.
//! @param[in] numChars     numChars - the number of characters to be read from the file.
//! @param[in] *stream       *stream - a pointer to a structure of the FILE type.
//!
//! @return a string that contains characters from a file.
//!
//! @brief writes the specified number of characters from the file to the str string.
//!
//---------------------------------------------------------------------------------------------------
char* myFgets( char* str, int numChars, FILE* stream );

//---------------------------------------------------------------------------------------------------
//!
//! @param[in] line     line - const string.
//!
//! @return the line that was copied, or NULL if memory could not be allocated.
//!
//! @brief Allocates memory for copying the line string and copies it.
//!
//---------------------------------------------------------------------------------------------------
char* myStrdup( const char* line );

//---------------------------------------------------------------------------------------------------
//!
//! @param[in] **line     **line - pointer to the buffer.
//! @param[in] *n        *n - pointer to allocated memory.
//! @param[in] *stream    *stream - a pointer to a FILE type structure.
//!
//! @return Allocated amount of memory.
//!
//! @brief Reads the drain from the input stream.
//!
//---------------------------------------------------------------------------------------------------
ssize_t myGetline( char** line, size_t* n, FILE* stream );

//----------------------------------------------------------------------------------------------------
//!
//! @param[in] *first   *first - the first constant string.
//! @param[in] *second  *second - the second constant string.
//! @param[in] key      key - the key by which the sorting takes place.
//!
//! @return the value is less than zero if the first string is lexicographically less than the first, 
//          0 if the strings are equal, otherwise 1
//!
//! @brief compares two strings character by character, skipping all characters that are not letters.
//!
//---------------------------------------------------------------------------------------------------
int myStrcmp( const char* first, const char* second, int key );

//--------------------------------------------------------------------------------------------------
//!
//! @param[in] *lineFromText    *lineFromText - a line from a text file or from another stream.
//!
//! @return a pointer to the first character of a string that is a letter.
//!
//! @brief cleans the front of the string from non-letter characters.
//!
//---------------------------------------------------------------------------------------------------
char* cleanLine( char* lineFromText );

#endif