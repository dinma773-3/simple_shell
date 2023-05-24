#include "shell.h"

/**
 * _myhistory - displays the commands history with list numbers
 * @info: structure holding possible arguments
 *
 *  Return: Always 0
 */
int _myhistory(info_t *info)
{
  print_list(info->history);
  return (0);
}

/**
 * unset_alias - sets alias to an empty string
 * @info: parameter struct
 * @str: the string representing the alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
  char *j;
  int ret;

  j = _strchr(str, '=');
  if (!j)
    return (1);

  *j = 0;
  ret = unset_alias(info, str);
  *j = '=';

  if (ret == 0)
    return 0;
  else
    return (1);
}

/**
 * set_alias - sets alias to a string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
  char *j;

  j = _strchr(str, '=');
  if (!j)
    return (1);
  if (!*++j)
    return unset_alias(info, str);

  unset_alias(info, str);
  return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - displays an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
  char *j = NULL, *i = NULL;

  if (node)
    {
      j = _strchr(node->str, '=');
      for (i = node->str; i <= j; i++)
	_putchar(*i);
      _putchar('\'');
      _puts(j + 1);
      _puts("'\n");
      return (0);
    }
  return (1);
}

/**
 * _myalias - simulates the behaviour of the alias, man alias
 * @info: structure containing potential arguments
 *
 *  Return: Always 0
 */
int _myalias(info_t *info)
{
  int a = 0;
  char *b = NULL;
  list_t *nodes = NULL;

  if (info->argc == 1)
    {
      nodes = info->alias;
      while (nodes)
	{
	  print_alias(nodes);
	  nodes = nodes->next;
	}
      return (0);
    }
  for (a = 1; info->argv[a]; a++)
    {
      b = _strchr(info->argv[a], '=');
      if (b)
	set_alias(info, info->argv[a]);
      else
	print_alias(node_starts_with(info->alias, info->argv[a], '='));
    }

  return (0);
}
