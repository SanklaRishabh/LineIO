#include "lineio.h"
#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>

size_t _c_getline(char **buf, size_t *bufSize, FILE *stream) {
    // Check whether the eof indicator is set.
    if (feof(stream)) {
        return READ_ERROR;
    }

    // Check parameters.
    // `buf` and `bufSize` cannot be NULL.
    if (buf == NULL || bufSize == NULL) {
        return errno = EINVAL;
    }

    if (*bufSize == 0) {
        // Default size of the buffer.
        *bufSize = 120;
        *buf = (char *)malloc(*bufSize * sizeof(char));

        // Failure in allocating memory.
        if (*buf == NULL) {
            perror("realloc");

            return errno = ENOMEM;
        }
    }

    bool eofCheck;
    char charBuf;
    char *failsafe;
    long startPos, endPos;
    startPos = ftell(stream);
    eofCheck = false;

    while ((charBuf = fgetc(stream))) {
        if (charBuf == '\n' || charBuf == EOF) {
            endPos = ftell(stream);
            size_t posDif = (size_t)(endPos - startPos);
            failsafe = *buf;

            // Reallocate new size to the buffer.
            if (posDif >= 2 * *bufSize) {
                *buf = (char *)realloc(*buf, (*bufSize = posDif + 1));
            } else if (posDif >= *bufSize) {
                *buf = (char *)realloc(*buf, (*bufSize *= 2));
            }

            // Failure in allocating memory.
            if (*buf == NULL) {
                perror("realloc");

                *buf = failsafe;

                return errno = ENOMEM;
            }

            if (charBuf == EOF) {
                eofCheck = true;
            }

            // Store the line in the buffer.
            // CAUTION: Seeking resets eof indicator.
            fseek(stream, startPos, SEEK_SET);
            fgets(*buf, *bufSize, stream);
            fseek(stream, endPos, SEEK_SET);

            break;
        }
    }

    if (eofCheck) {
        // Set the eof indicator again.
        fgetc(stream);
        fgetc(stream);
    }

    // Successful line read.
    return *bufSize;
}
