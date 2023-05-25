#include <unistd.h>
#include "shell.h"

/**
 * _eputchar - Writes a character to the standard error
 * @c: The character to be written
 *
 * Return: On success, 1 is returned. On error, -1 is returned.
 */
int _eputchar(char c)
{
return write(STDERR_FILENO, &c, 1);
}

/**
 * _erratoi - Converts a string to an integer
 * @str: The string to be converted
 *
 * Return: The converted integer value
 */
int _erratoi(char *str)
{
int result = 0;
int sign = 1;
int i = 0;

if (str == NULL)
return 0;


if (str[0] == '-')
{
sign = -1;
i++;
}

while (str[i] != '\0')
{
if (str[i] >= '0' && str[i] <= '9')
{
result = result * 10 + (str[i] - '0');
i++;
}
else
{

return 0;
}
}

return result * sign;
}

/**
 * _eputs - Prints a string to the standard error
 * @str: The string to be printed
 *
 * Return: None
 */
void _eputs(char *str)
{
int i = 0;

if (str == NULL)
return;

while (str[i] != '\0')
{
_eputchar(str[i]);
i++;
}
}

/**
 * _puts - Prints a string to the standard output
 * @str: The string to be printed
 *
 * Return: None
 */
void _puts(char *str)
{
int i = 0;

if (str == NULL)
return;

while (str[i] != '\0')
{
_putchar(str[i]);
i++;
}
}

/**
 * ffree - Frees a double pointer array of strings
 * @arr: The double pointer array to be freed
 *
 * Return: None
 */
void ffree(char **arr)
{
int i;

if (arr == NULL)
return;

for (i = 0; arr[i] != NULL; i++)
free(arr[i]);

free(arr);
}
