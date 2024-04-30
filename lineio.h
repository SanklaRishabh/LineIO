/*
 * lineio.h
 *
 * Declarations for Windows-equivalent
 * implementations of POSIX I/O functions.
*/
#ifndef _LINEIO_H
#define _LINEIO_H

#define READ_ERROR -1 

#include <stdio.h>

size_t _c_getline(char **, size_t *, FILE *);

#endif
