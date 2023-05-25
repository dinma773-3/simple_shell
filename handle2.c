#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
/**
 * add_node_end - Adds a new node at the end of a linked list
 * @head: Double pointer to the head of the linked list
 * @str: String to be stored in the new node
 * @num: Number to be stored in the new node
 *
 * Return: Address of the new node, or NULL on failure
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
list_t *new_node;
list_t *last_node;

if (head == NULL)
return (NULL);

new_node = malloc(sizeof(list_t));
if (new_node == NULL)
return (NULL);

new_node->str = strdup(str);
if (new_node->str == NULL)
{
free(new_node);
return (NULL);
}

 new_node->num = num;
 new_node->next = NULL;

 if (*head == NULL)
 {
 *head = new_node;
 }
 else
 {
last_node = *head;
while (last_node->next != NULL)
last_node = last_node->next;
last_node->next = new_node;
}

return (new_node);
}

/**
 * build_history_list - Builds a history list from a buffer
 * @info: Pointer to the info_t structure
 * @buf: Buffer containing the history entries
 * @linecount: Line count
 *
 * Return: 0 on success, -1 on failure
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
char *token;
int count = 0;

if (info == NULL || buf == NULL)
return (-1);

token = strtok(buf, "\n");
while (token != NULL)
{
if (add_node_end(&(info->history), token, linecount + count) == NULL)
return (-1);

token = strtok(NULL, "\n");
count++;
}

return (0);
}


/**
 * check_chain - Checks if a command is part of a command chain
 * @info: Pointer to the info_t structure
 * @cmd: Command to check
 * @chain_type: Pointer to the chain type (CMD_OR, CMD_AND, or CMD_CHAIN)
 * @start_idx: Start index of the command chain
 * @end_idx: End index of the command chain
 *
 * This function updates the values of @chain_type, @start_idx, and @end_idx based on the type of command chaining
 * present in the given command.
 */
void check_chain(info_t *info, char *cmd, size_t *chain_type, size_t start_idx, size_t end_idx)
{
size_t i;
if (info == NULL || cmd == NULL || chain_type == NULL)
return;

*chain_type = CMD_NORM;

for (i = start_idx; i <= end_idx; i++)
{
if (cmd[i] == '|')
{
if (cmd[i + 1] == '|')
{
*chain_type = CMD_OR;
break;
}
else
{
*chain_type = CMD_CHAIN;
break;
}
}
else if (cmd[i] == '&')
{
if (cmd[i + 1] == '&')
{
*chain_type = CMD_AND;
break;
}
}
}
}

/**
 * free_list - Frees a linked list
 * @list: Pointer to the head of the linked list
 *
 * This function frees the memory occupied by each node in the linked list,
 * including the memory allocated for the string stored in each node.
 */
void free_list(list_t **list)
{
list_t *current = *list;
list_t *next;    
if (list == NULL || *list == NULL)
return;

while (current != NULL)
{
next = current->next;
free(current->str);
free(current);
current = next;
}

*list = NULL;
}

/**
 * is_chain - Checks if a command is part of a command chain
 * @info: Pointer to the info_t structure
 * @cmd: Command string
 * @index: Pointer to the index where the command chain ends
 *
 * This function checks if the given command string is part of a command chain
 * (e.g., command1 || command2, command1 && command2, command1 ; command2).
 * It updates the index to point to the position where the command chain ends.
 * Returns: 1 if it is a command chain, 0 otherwise.
 */
int is_chain(info_t *info, char *cmd, size_t *index)
{
size_t i;
size_t len = strlen(cmd);
(void)info;

if (cmd == NULL || len == 0)
return 0;

for (i = 0; i < len; i++)
{
if (cmd[i] == '|' && i < len - 1 && cmd[i + 1] == '|')
{
*index = i + 2;
return 1;
}
else if (cmd[i] == '&' && i < len - 1 && cmd[i + 1] == '&')
{
*index = i + 2;
return 1;
}
else if (cmd[i] == ';')
{
*index = i + 1;
return 1;
}
}

return 0;
}
