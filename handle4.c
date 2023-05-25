#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * print_list - Prints the elements of a linked list
 * @list: Pointer to the head of the list
 *
 * Return: The number of elements in the list
 */
size_t print_list(const list_t *list)
{
    size_t count = 0;
    
    while (list != NULL)
    {
        printf("%s\n", list->str);
        count++;
        list = list->next;
    }
    
    return count;
}

/**
 * print_error - Prints an error message
 * @info: Pointer to the info_t structure
 * @message: Error message to print
 */
void print_error(info_t *info, char *message)
{
    printf("%s: Error: %s\n", info->arg, message);
}

/**
 * print_list_str - Prints a list of strings
 * @list: Pointer to the list_t structure
 *
 * Return: Number of nodes in the list
 */
size_t print_list_str(const list_t *list)
{
    size_t count = 0;
    const list_t *current = list;

    while (current != NULL)
    {
        printf("%s\n", current->str);
        current = current->next;
        count++;
    }

    return count;
}

/**
 * list_to_strings - Converts a linked list of strings to an array of strings
 * @list: Pointer to the list_t structure
 *
 * Return: Pointer to the array of strings
 */
char **list_to_strings(list_t *list)
{
    size_t i;
    size_t count = 0;
    list_t *current = list;
    char **strings = NULL;

    while (current != NULL)
    {
        count++;
        current = current->next;
    }

    strings = malloc((count + 1) * sizeof(char *));
    if (strings == NULL)
    {
        perror("Memory allocation error");
        return NULL;
    }

    current = list;
    for (i = 0; i < count; i++)
    {
        strings[i] = current->str;
        current = current->next;
    }

    strings[count] = NULL;

    return strings;
}

/**
 * _strdup - Duplicates a string
 * @str: Pointer to the string to be duplicated
 *
 * Return: Pointer to the newly allocated duplicated string
 */
char *_strdup(const char *str)
{
    char *dup = NULL;
    size_t length = 0;

    if (str == NULL)
        return NULL;

    length = strlen(str);
    dup = malloc((length + 1) * sizeof(char));
    if (dup == NULL)
    {
        perror("Memory allocation error");
        return NULL;
    }

    strcpy(dup, str);

    return dup;
}

