#include "shell.h"

/**
 **_strncpy - copies a string
 *@dest: destination string to be copied to
 *@src: source string to copy from
 *@n: the amount of characters to be copied
 *
 *Return: the concatenated string
 */
char *_strncpy(char *dest, char *src, int n)
{
  int p, s;
  char *i = dest;

  p = 0;
  while (src[p] != '\0' && p < n - 1)
    {
      dest[p] = src[p];
      p++;
    }
  if (p < n)
    {
      s = p;
      while (s < n)
	{
	  dest[s] = '\0';
	  s++;
	}
    }
  return (i);
}

/**
 **_strncat - concatenates two strings
 *@dest: the first string to concatenate
 *@src: the second string to concatenate
 *@n: maximum number of bytes to be used for src
 *
 *Return: the concatenated string
 */
char *_strncat(char *dest, char *src, int n)
{
  int a, b;
  char *i = dest;

  a = 0;
  b = 0;
  while (dest[a] != '\0')
    a++;
  while (src[b] != '\0' && b < n)
    {
      dest[a] = src[b];
      a++;
      b++;
    }
  if (b < n)
    dest[a] = '\0';
  return (i);
}

/**
 * _strchr - locates a character in a string
 * @s: the string to be located
 * @c: the character to look for
 *
 * Return: (s) a pointer to the memory area s
 */
char *_strchr(char *s, char c)
{
  do
    {
      if (*s == c)
	return (s);
    }
  while (*s++ != '\0');

  return (NULL);
}
