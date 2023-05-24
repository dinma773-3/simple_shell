#include "shell.h"
#include <errno.h>
#include <sys/wait.h>

/**
 * hsh - primary loop of the shell
 * @info: pointer to the info_t structure 
 * @av: argument vector from main function
 *
 * Return: 0 on success, 1 on error, or error code
 */

int hsh(info_t *info, char **av)
{
  ssize_t i = 0;
  int builtin = 0;

  while (i != -1 && builtin != -2)
  {
    clear_info(info);
    if (interactive(info))
    {
      _puts("$ ");
      _eputchar(BUFF_FLUSH);
    }
    i = get_input(info);
    if (i != -1)
    {
      set_info(info, av);
      builtin = find_builtin(info);
      if (builtin == -1)
        find_cmd(info);
    }
    else if (interactive(info))
    {
      _putchar('\n');
    }
    free_info(info, 0);
  }

  write_history(info);
  free_info(info, 1);
  
  if (!interactive(info) && info->status)
    exit(info->status);
  
  if (builtin == -2)
  {
    if (info->err_num == -1)
      exit(info->status);
    exit(info->err_num);
  }
  
  return (builtin);
}

/**
 * find_builtin - looks for a builtin command
 * @info: pointer to the into_t structure
 *
 * Return: -1 if builtin is not found,
 * 	0 if builtin is executed successfully,
 * 	1 if builtin is found but not successful,
 * 	2 if builtin signals exit()
 */
int find_builtin(info_t *info)
{
  int j, built_in = -1;

  builtin_t builtintbl[] =
    {
     {"exit", _myexit},
     {"env", _myenv},
     {"help", _myhelp},
     {"history", _myhistory},
     {"setenv", _mysetenv},
     {"unsetenv", _myunsetenv},
     {"cd", _mycd},
     {"alias", _myalias},
     {NULL, NULL}
    };

  for (j = 0; builtintbl[j].type; j++)
    {
    if (_strcmp(info->argv[0], builtintbl[j].type) == 0)
    {
      info->line_count++;
      built_in = builtintbl[j].func(info);
      break;
    }
  }
  return built_in;
}

/**
 * find_cmd - locates a command in PATH
 * @info: the parameter
 *
 * Return: void
 */
void find_cmd(info_t *info)
{
  char *cmd = NULL;
  int i, j;

  info->cmd = info->argv[0];
  if (info->linecount_flag == 1)
  {
    info->line_count++;
    info->linecount_flag = 0;
  }
  for (i = 0, j = 0; info->arg[i]; i++)
  {
    if (!is_delim(info->arg[i], " \t\n"))
      j++;
  }
  if (j == 0)
    return;

   cmd = find_path(info, _getenv(info, "PATH="), info->argv[0]);
  if (cmd)
  {
    info->cmd = cmd;
    fork_cmd(info);
  }
  else
  {
    if ((interactive(info) || _getenv(info, "PATH=") || info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
    {
      fork_cmd(info);
    }
    else if (*(info->arg) != '\n')
    {
      info->status = 127;
      print_error(info, "not found\n");
    }
  }
}

/**
 * fork_cmd - creates a child process to execude cmd
 * @info: parameter & return info struct
 *
 * Return: void
 */
void fork_cmd(info_t *info)
{
  int jute;
  pid_t child_pid;

  child_pid = fork();
  if (child_pid == -1)
  {
    perror("Error:");
    return;
  }
  if (child_pid == 0)
  {
    if (execve(info->path, info->argv, info->env) == -1)
    {
            free_info(info, 1);
      if (errno == EACCES)
        exit(126);
      exit(1);
    }
  }
  else
  {
    wait(&jute);
    if (WIFEXITED(jute))
      info->jute = WEXITSTATUS(jute);
    else if (WIFSIGNALED(jute))
      info->jute = WTERMSIG(jute) + 126;
  }
}
