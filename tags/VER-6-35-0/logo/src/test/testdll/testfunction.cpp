//////////////////////////////////////////////////////////////////////////////
// testfunction.cpp
// 
// This file contains some functions that get exported from a DLL that can
// be used to test various aspects of DLLCALL.
//
#include <windows.h>
#include <stdio.h>


// A simple function that takes a double as a parameter and returns a double.
//
// It can be called like
//   DLLCALL [F MakeSquare@8 F 2.2 ]
//
extern "C"
__declspec(dllexport)
double
WINAPI
MakeSquare(double Number)
{
    return Number * Number;
}


// A simple function that takes a double as a parameter and returns a string.
//
// It can be called like
//   DLLCALL [S FormatFloat@8 F 2.2 ]
//
extern "C"
__declspec(dllexport)
char *
WINAPI
FormatFloat(double Number)
{
    // Allocate a buffer to hold the return string
    size_t bufferSize     = 64;
    char * formattedFloat = static_cast<char*>(GlobalAlloc(GPTR, bufferSize));

    // Format the number to the string
    snprintf(formattedFloat, bufferSize, "%f", Number);

    // Return the string
    return formattedFloat;
}

// A simple function that takes a WORD as a parameter and returns a string.
//
// It can be called like
//   DLLCALL [S FormatWord@4 W 123 ]
//
extern "C"
__declspec(dllexport)
char *
WINAPI
FormatWord(WORD Number)
{
    // Allocate a buffer to hold the return string
    size_t bufferSize     = 64;
    char * formattedWord = static_cast<char*>(GlobalAlloc(GPTR, bufferSize));

    // Format the number to the string
    snprintf(formattedWord, bufferSize, "%d", Number);

    // Return the string
    return formattedWord;
}
