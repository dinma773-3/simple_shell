#include "shell.h"
#include <sys/stat.h>

/**
 * is_cmd - checks if the given path corresponds to a regular file
 * @info: pointer to info_t structure (unused)
 * @path: path to check 
 *
 * Return: 1 if the path corresponds to a regular file
 *  0 otherwise 
 */
int is_cmd(info_t *info, char *path)
{
  struct stat st;
  (void)info;

  if (!path || stat(path, &st))
    return 0;

  if (st.st_mode & S_IFREG)
    return 1;

  return 0;
}

/**
 * dup_chars - duplicates characters from a given path string
 * @pathstr: PATH string to duplicate
 * @start: starts index of the characters to duplicate 
 * @stop: stops index of the characters to duplicate 
 *
 * Return: pointer to buffer containing the duplicated characers
 */

char *dup_chars(char *pathstr, int start, int stop)
{
  int length = stop - start;
  char *buffer = malloc((length + 1) * sizeof(char));
  int i = 0, j = 0;

  if (buffer == NULL)
    return NULL;

  for (i = start; i < stop; i++)
  {
    if (pathstr[i] != ':')
      buffer[j++] = pathstr[i];
  }
  buffer[j] = '\0';
  return buffer;
}

/**
 * find_path - finds the given command in the PATH string
 * @info: points to the info struct
 * @pathstr: PATH string to search
 * @cmd: command to find
 * 
 * Return: path of the command if found, or NULL if not found
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
  int j = 0;
  int current = 0;
  char *path;

  if (!pathstr)
    return NULL;
  if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
  {
    if (is_cmd(info, cmd))
      return cmd;
  }
  while (pathstr[j])
  {
    if (pathstr[j] == ':')
    {
      path = malloc(j - current + 2);
      if (!path)
        return NULL;
      
      _strcat(path, "/");
      _strcat(path, cmd);

      if (is_cmd(info, path))
        return path;
      free(path);

      if (!pathstr[j])
        break;
      current = j + 1;
    }
    j++;
  }
  return NULL;
}
