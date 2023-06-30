#include "lineio.h"

ssize_t readline(char **buffer, FILE *ptr) {
    *buffer = NULL;
    size_t bufSize = 0;
    char charBuf;

    while ((charBuf = fgetc(ptr)) != EOF && charBuf != '\n') {
        *buffer = realloc(*buffer, bufSize + 1);

        if (*buffer == NULL) {
            perror("realloc()");

            return ALLOCATION_FAILURE;
        }

        (*buffer)[bufSize++] = charBuf;
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
    return (ssize_t)bufSize;
}
