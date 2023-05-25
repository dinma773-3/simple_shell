#include <stdio.h>
#include <stdlib.h>
#include "shell.h"

/**
 * node_starts_with - Searches for a node with a string that starts with a given prefix
 * @head: Pointer to the head of the list
 * @prefix: Prefix string to search for
 * @ignore_case: Flag indicating whether the search should be case-insensitive (0 - case-sensitive, 1 - case-insensitive)
 *
 * Return: Pointer to the first node with a matching prefix, or NULL if not found
 */
list_t *node_starts_with(list_t *head, char *prefix, char ignore_case)
{
    list_t *current = head;

    while (current != NULL)
    {
        if (ignore_case == 0)
        {
            if (strncmp(current->str, prefix, strlen(prefix)) == 0)
                return current;
        }
        else
        {
            if (strncasecmp(current->str, prefix, strlen(prefix)) == 0)
                return current;
        }

        current = current->next;
    }

    return NULL;
}

/**
 * delete_node_at_index - Deletes a node at a given index in a linked list
 * @head: Pointer to the head of the list
 * @index: Index of the node to delete (starting from 0)
 *
 * Return: 1 if successful, 0 if the index is out of range
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
    list_t *current;
    list_t *previous;
    unsigned int i;
    if (head == NULL || *head == NULL)
        return 0;

    if (index == 0)
    {
        list_t *temp = *head;
        *head = temp->next;
        free(temp->str);
        free(temp);
        return 1;
    }

    current = *head;
    previous = NULL;
    

    for (i = 0; i < index && current != NULL; i++)
    {
        previous = current;
        current = current->next;
    }

    if (current == NULL)
        return 0;

    previous->next = current->next;
    free(current->str);
    free(current);
    return 1;
}

/**
 * get_history_file - Retrieves the history file path
 * @info: Pointer to the info_t structure
 *
 * Return: Pointer to the history file path string
 */
char *get_history_file(info_t *info)
{
    size_t home_dir_len;
    size_t fname_len;
    char *home_dir;
    char *history_file;

    if (info == NULL || info->fname == NULL)
        return NULL;

    home_dir = _getenv(info, "HOME");
    if (home_dir == NULL)
        return NULL;

    home_dir_len = strlen(home_dir);
    fname_len = strlen(info->fname);

    history_file = malloc(home_dir_len + fname_len + 2);
    if (history_file == NULL)
    {
        perror("Memory allocation error");
        free(home_dir);
        return NULL;
    }

    strcpy(history_file, home_dir);
    history_file[home_dir_len] = '/';
    strcpy(&history_file[home_dir_len + 1], info->fname);

    free(home_dir);

    return history_file;
}
