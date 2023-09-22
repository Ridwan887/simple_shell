#include "shell.h"

/**
 * fillMemory - Fills memory with a constant byte.
 * @destination: Pointer to the memory area.
 * @byte: The byte to fill *destination with.
 * @size: The number of bytes to be filled.
 * Return: A pointer to the memory area destination.
 */
char *fillMemory(char *destination, char byte, unsigned int size)
{
    unsigned int i;

    for (i = 0; i < size; i++) {
        destination[i] = byte;
    }
    return destination;
}

/**
 * freeArrayOfStrings - Frees an array of strings.
 * @strArray: Array of strings.
 */
void freeArrayOfStrings(char **strArray)
{
    char **currentPtr = strArray;

    if (!strArray)
        return;
    
    while (*strArray) {
        free(*strArray);
        strArray++;
    }
    
    free(currentPtr);
}

/**
 * reallocateMemory - Reallocates a block of memory.
 * @previousPtr: Pointer to the previous malloc'ed block.
 * @oldSize: Byte size of the previous block.
 * @newSize: Byte size of the new block.
 *
 * Return: Pointer to the reallocated block.
 */
void *reallocateMemory(void *previousPtr, unsigned int oldSize, unsigned int newSize)
{
    if (!previousPtr) {
        return malloc(newSize);
    }
    
    if (!newSize) {
        free(previousPtr);
        return NULL;
    }
    
    if (newSize == oldSize) {
        return previousPtr;
    }

    void *newPtr = malloc(newSize);
    if (!newPtr) {
        return NULL;
    }

    memcpy(newPtr, previousPtr, oldSize < newSize ? oldSize : newSize);
    free(previousPtr);
    return newPtr;
}
