# <p style = "text-align: center">Line I/O - Readline</p>

<p style = "text-align: right">
    <img src = "https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white">
    <img src = "https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white">
</p>

`readline` is a function that reads a line from the specified stream and dynamically allocates memory to store the line in a buffer. It is similar to `getline` that is part of the POSIX standard, but not a part of the C standard library or the Windows API.

## Navigation

+ [Usage](#usage)
+ [Inclusion](#inclusion)
+ [Parameters](#parameters)
+ [Return Value](#return-value)
+ [Example](#example)
+ [Warning](#warning)

## Usage

To use `readline`, download the `lineio.h` and `liblineio.a` resource files into your project folder and link to create an executable using:
```powershell
# GNU GCC Compiler

gcc -std=c99 -Wall -llineio -o <OUTPUT_FILE> <SOURCE_FILE>

# If the library is not in the same directory as the source file, use the -L flag to specify the path to the library file.

gcc -std=c99 -Wall -L <PATH_TO_LIBRARY> -llineio -o <OUTPUT_FILE> <SOURCE_FILE>
```

## Inclusion

The library already includes the `basetsd.h` header file, so there is no need to include it again in the source code. However, the `stdio.h`, `stdlib.h`, and the `lineio.h` header files must be included.

The code is well protected with header guards to prevent cases of multiple inclusion.

## Parameters

The `readline` function takes two parameters:
>*&str*
+ Address to the pointer to the character buffer where the line read is stored.

>*stream*
+ Pointer to the `FILE` object that identifies an input stream.
+ `stdin` can be used as an argument to read from the standard input.

## Return Value

On **success**, the function returns the number of characters (or bytes) read from the stream, excluding the line delimiter, `'\n'`.

If a blank stream is tried to be read, the function returns **`EMPTY_READ`**, which is equivalent to **0**.

If memory allocation fails, the function returns **`ALLOCATION_FAILURE`**, which is equivalent to **-1**.

## Example

```c
#include "lineio.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");

    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    char *buffer;
    ssize_t bytesRead = readline(&buffer, fp);

    printf("%zd\n", bytesRead);
    fclose(fp);
    free(buffer);

    return 0;
}
```

## Warning

The `readline` function uses `malloc` to dynamically allocate memory to store the line read from the stream. It does not free the memory allocated to the buffer. It is the responsibility of the programmer to free the memory allocated to the buffer after use. However, there will be a fix to this in a future version.

Example:
```c
while (readline(&buffer, fp) != EMPTY_READ) {
    // Do something with the buffer
    free(buffer);
}
```