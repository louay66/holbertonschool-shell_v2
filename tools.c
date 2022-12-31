#include "main.h"

/**
 * my_realloc -  * block of memory of the specified
 * size using the malloc function
 * @ptr: pointer of previse block
 * @new_size: size of new block
 *
 * Return: new block
 */

void *my_realloc(void *ptr, size_t new_size)
{
	void *new_ptr = malloc(new_size);

	if (!new_ptr)
	{
		/*Allocation failed*/
		return (NULL);
	}
	if (ptr)
	{
		_memcpy(new_ptr, ptr, new_size);
		free(ptr);
	}
	return (new_ptr);
}
/**
 * _strcmp - compares 2 strings
 * @s1: pointer to 1st string
 * @s2: pointer to 2nd string
 *
 * Return: difference between s1 and s2
 */

int _strcmp(char *s1, char *s2)
{
	int i = 0;

	while ((s1[i] != '\0' && s2[i] != '\0') && s1[i] == s2[i])
	{
		i++;
	}

	return (s1[i] - s2[i]);
}

/**
 **_memcpy - overwrite parte of  data stractar
 *@dest:array
 *@src:the new value
 *@n: numbar of the value overwrite
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
char *_memcpy(char *dest, char *src, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
	{
		dest[i] = src[i];
	}
	return (dest);
}
