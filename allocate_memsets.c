#include "shell.h"

/**
 * fillMemory - fills memory with a constant byte
 * @destination: Pointer to the memory area
 * @byte: The byte to fill *destination with
 * @size: The amount of bytes to be filled
 * Return: A pointer to the memory area destination
 */
char *fillMemory(char *destination, char byte, unsigned int size)
{
	unsigned int g;

	for (g = 0; g < size; g++)
		destination[g] = byte;
	return (destination);
}

/**
 * freeArrayOfStrings - frees an array of strings
 * @strArray: Array of strings
 */
void freeArrayOfStrings(char **strArray)
{
	char **currentPtr = strArray;

	if (!strArray)
		return;
	while (*strArray)
		free(*strArray++);
	free(currentPtr);
}

/**
 * reallocateMemory - reallocates a block of memory
 * @prPtr: Pointer to the previous malloc'ated block
 * @oldSize: Byte size of the previous block
 * @newSize: Byte size of the new block
 *
 * Return: Pointer to the old block's nameen.
 */
void *reallocateMemory(void *prPtr, unsigned int oldSize, unsigned int newSize)
{
	char *newPtr;

	if (!prPtr)
		return (malloc(newSize));
	if (!newSize)
		return (free(prPtr), NULL);
	if (newSize == oldSize)
		return (prPtr);
	newPtr = malloc(newSize);
	if (!newPtr)
		return (NULL);
	oldSize = oldSize < newSize ? oldSize : newSize;
	while (oldSize--)
		newPtr[oldSize] = ((char *)prPtr)[oldSize];
	free(prPtr);
	return (newPtr);
}
