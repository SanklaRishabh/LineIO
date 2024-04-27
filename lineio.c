#include "lineio.h"
#include <stdlib.h>

size_t readline(char **buffer, FILE *ptr) {
  *buffer = NULL;
  size_t bufSize = 0;
  char charBuf;

  while ((charBuf = fgetc(ptr)) != EOF) {
    *buffer = realloc(*buffer, bufSize + 1);

    if (*buffer == NULL) {
      perror("realloc()");

      return ALLOCATION_FAILURE;
    }

    (*buffer)[bufSize++] = charBuf;

    if (charBuf == '\n') {
      break;
    }
  }

  if (bufSize == 0 && charBuf == EOF) {
    return EMPTY_READ;
  }

  *buffer = realloc(*buffer, bufSize + 1);

  if (*buffer == NULL) {
    perror("realloc()");

    return ALLOCATION_FAILURE;
  }

  (*buffer)[bufSize] = '\0';

  // Line reading successful.
  return (size_t)bufSize;
}
