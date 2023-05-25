#include "shell.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

/**
 * remove_comments - Removes comments from a string by replacing them with null terminators
 * @str: The string to remove comments from
 */
void remove_comments(char *str)
{
int in_comment = 0;
char *ptr = str;

if (str == NULL)
return;

while (*ptr != '\0')
{
if (*ptr == '#' && !in_comment)
{
*ptr = '\0';
break;
}
else if (*ptr == '"' && *(ptr - 1) != '\\')
{
in_comment = !in_comment;
}
ptr++;
}
}

/**
 * replace_alias - Replaces command aliases in the command buffer with their corresponding values
 * @info: Pointer to the info_t structure
 *
 * Return: 0 on success, -1 on failure
 */
int replace_alias(info_t *info)
{
int i;
list_t *alias_list = info->alias;
char **cmd_buf = info->cmd_buf;

if (info == NULL || alias_list == NULL || cmd_buf == NULL)
return -1;

for (i = 0; cmd_buf[i] != NULL; i++)
{
char *alias = cmd_buf[i];
list_t *alias_node = node_starts_with(alias_list, alias, '=');

if (alias_node != NULL)
{
char *alias_value = strchr(alias_node->str, '=');
if (alias_value != NULL)
{
alias_value++;

free(cmd_buf[i]);
cmd_buf[i] = _strdup(alias_value);
if (cmd_buf[i] == NULL)
return -1;
}
}
}

return 0;
}

int replace_vars(info_t *info)
{
    char *cmd;
    size_t cmd_len;
    size_t var_start;
    size_t var_end;
    char *var_name;
    size_t var_name_length;
    char *var_value;
    if (info == NULL || info->cmd == NULL)
        return 0;

    cmd = info->cmd;
    cmd_len = strlen(cmd);
    var_start = 0;
    var_end = 0;
    var_name = NULL;
    var_name_length = 0;
    var_value = NULL;

    while (var_end < cmd_len)
    {
        if (cmd[var_end] == '$')
        {
            var_start = var_end;
            var_end++;
            while (isalnum(cmd[var_end]) || cmd[var_end] == '_')
                var_end++;

            var_name_length = var_end - var_start - 1;
            var_name = malloc(var_name_length + 1);
            if (var_name == NULL)
            {
                perror("Memory allocation error");
                return 0;
            }
            strncpy(var_name, &cmd[var_start + 1], var_name_length);
            var_name[var_name_length] = '\0';

            var_value = _getenv(info, var_name);
            free(var_name);

            if (var_value != NULL)
            {
                size_t var_value_length = strlen(var_value);
                size_t replace_length = var_value_length + var_end - var_start - 1;

                char *new_cmd = realloc(cmd, cmd_len + replace_length);
                if (new_cmd == NULL)
                {
                    perror("Memory allocation error");
                    free(var_value);
                    return 0;
                }

                cmd = new_cmd;
                memmove(&cmd[var_start + var_value_length + 1], &cmd[var_end], cmd_len - var_end);
                memcpy(&cmd[var_start], var_value, var_value_length);

                cmd_len += replace_length;
                var_end = var_start + var_value_length;
                free(var_value);
            }
            else
            {
                var_end = var_start + 1;
            }
        }
        else
        {
            var_end++;
        }
    }

    info->cmd = cmd;
    return 1;
}

/**
 * starts_with - Checks if a string starts with a specified prefix
 * @str: The string to check
 * @prefix: The prefix to compare with
 *
 * Return: Pointer to the position in @str after the prefix if it starts with the prefix, otherwise NULL.
 */
char *starts_with(const char *str, const char *prefix)
{
size_t str_len;
size_t prefix_len;
if (str == NULL || prefix == NULL)
return NULL;

str_len = strlen(str);
prefix_len = strlen(prefix);

if (str_len < prefix_len)
return NULL;

if (strncmp(str, prefix, prefix_len) == 0)
return (char *)(str + prefix_len);

return NULL;
}

/**
 * write_history - Writes the command history to a file
 * @info: Pointer to the info_t structure
 *
 * Return: 1 on success, 0 on failure
 */
int write_history(info_t *info)
{
char *history_file;
FILE *file;
list_t *node = info->history;
if (info == NULL || info->history == NULL)
return 0;

history_file = get_history_file(info);
if (history_file == NULL)
return 0;

file = fopen(history_file, "w");
if (file == NULL)
{
perror("Error opening history file");
free(history_file);
return 0;
}

while (node != NULL)
{
fprintf(file, "%s\n", node->str);
node = node->next;
}

fclose(file);
free(history_file);
return 1;
}

