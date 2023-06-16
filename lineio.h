#ifndef READLINE_H
#define READLINE_H

#define ALLOCATION_FAILURE -1
#define EMPTY_READ 0

#include <basetsd.h>
#include <stdio.h>
#include <stdlib.h>

typedef SSIZE_T ssize_t;

ssize_t readline(char**, FILE*);

#endif