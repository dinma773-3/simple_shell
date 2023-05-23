#include "shell.h"

/**
 * _myexit - terminates the shell
 * @info: Structure containing possible arguments
 *
 * Return: exits with a given exit status
 */
int _myexit(info_t *info)
{
  int check;

  if (info->argv[1])
    {
      check = _erratoi(info->argv[1]);
      if (check == -1)
	{
	  info->status = 2;
	  print_error(info, "Illegal number: ");
	  _eputs(info->argv[1]);
	  _eputchar('\n');
	  return (1);
	}
      info->err_num = _erratoi(info->argv[1]);
      return (-2);
    }
  info->err_num = -1;
  return (-2);
}

/**
 * _mycd - updates the current directory of the process
 * @info: Structure holding possible arguments
 *
 * Return: Always 0 (success)
 */
int _mycd(info_t *info)
{
  char *j, *directory, buff[1024];
  int check_dir_ret;

  j = getcwd(buff, 1024);
  if (!j)
    _puts("TODO: >>getcwd failure emsg here<<\n");

  if (!info->argv[1])
    {
      directory = _getenv(info, "HOME=");
      if (!directory)
	check_dir_ret = chdir((directory = _getenv(info, "PWD=")) ? directory : "/");
      else
	check_dir_ret = chdir(directory);
    }

  else if (_strcmp(info->argv[1], "-") == 0)
    {
      if (!_getenv(info, "OLDPWD="))
	{
	  _puts("TODO: >>OLDPWD not set emsg here<<\n");
	  return (0);
	}
       directory = _getenv(info, "OLDPWD=");
       check_dir_ret = chdir(directory);
    }
  else
    {
      directory = info->argv[1];
      check_dir_ret = chdir(directory);
    }

  if (check_dir_ret == -1)
    {
      _puts("TODO: >chdir failure emsg here<<\n");
      return 0;
    }
  return 0;
}

/**
 * _myhelp - provides assistance or information to the user
 * @info: structure holding possible arguments
 *
 * Return: Always success 0
 */
int _myhelp(info_t *info)
{
  char **array;

  array = info->argv;
  _puts("help call works. Function not yet implemented \n");
  if (0)
    _puts(*array);
  return (0);
}
