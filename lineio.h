#ifndef READLINE_H
#define READLINE_H

#define ALLOCATION_FAILURE -1
#define EMPTY_READ 0

#include <basetsd.h>

size_t readline(char**, FILE*);

#endif