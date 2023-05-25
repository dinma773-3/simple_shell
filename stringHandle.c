#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * _strlen - returns the length of a string
 *
 * @s: string to be counted
 *
 * Return: length of string
 */
int _strlen(char *s)
{
int len = 0;

while (s[len])
len++;

return (len);

}

/**
 * _strcpy - copy the string pointed to by scr
 * @dest: destination
 * @src: source
 * Return: the pointer to dest
 */

char *_strcpy(char *dest, char *src)
{
int count;

for (count = 0; src[count] != '\0'; count++)
dest[count] = src[count];
dest[count] = '\0';

return (dest);
}

/**
 * _strcat - concatenates from one string to another
 * @dest: destination
 * @src: source
 *
 * Return: a pointer to the resulting string
 */
char *_strcat(char *dest, char *src)
{
int i, j;

i = 0;
j = 0;

while (dest[i] != '\0')
i++;

while (src[j] != '\0')
{
dest[i] = src[j];
i++;
j++;
}

dest[i] = '\0';

return (dest);
}

/**
 * _strcmp - a function that compares two string values
 * @s1: input value 1
 * @s2: input value 2
 *
 * Return: s1[i] - s2[i]
 */
int _strcmp(char *s1, char *s2)
{
int i;

i = 0;
while (s1[1] != '\0' && s2[i] != '\0')
{
if (s1[i] != s2[i])
{
return (s1[i] - s2[i]);
}
i++;
}
return (0);
}


/**
 * strtow - Splits a string into an array of strings based on delimiters
 * @str: The string to be split
 * @delimiters: The string containing delimiters
 * Return: Pointer to an array of strings (or NULL if it fails)
 */
char **strtow(char *str, char *delimiters)
{
char **str_array;
int i, j, k, words, len, start;

if (str == NULL || *str == '\0' || delimiters == NULL || *delimiters == '\0')
return NULL;

len = strlen(str);
words = 0;
start = 0;


for (i = 0; i <= len; i++)
{
if (strchr(delimiters, str[i]) || str[i] == '\0')
{
if (i > 0 && !strchr(delimiters, str[i - 1]))
words++;
start = 0;
}
else if (start == 0)
start = 1;
}


str_array = malloc((words + 1) * sizeof(char *));
if (str_array == NULL)
return NULL;


start = 0;
j = 0;
for (i = 0; i <= len; i++)
{
if (strchr(delimiters, str[i]) || str[i] == '\0')
{
if (i > 0 && !strchr(delimiters, str[i - 1]))
{
str_array[j] = malloc((i - start + 1) * sizeof(char));
if (str_array[j] == NULL)
{

for (k = 0; k < j; k++)
free(str_array[k]);
free(str_array);
return NULL;
}

strncpy(str_array[j], &str[start], i - start);
str_array[j][i - start] = '\0';
j++;
}
start = 0;
}
else if (start == 0)
start = i;
}

str_array[words] = NULL; /* Set the last element to NULL */

return str_array;
}
