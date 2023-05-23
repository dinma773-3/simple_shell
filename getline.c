#include "shell.h"
#include <signal.h>

/**
 * input_buf - buffering a series of commands
 * @info: parameter struct
 * @buf: address of the buffer
 * @len: address of len variable
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
  ssize_t i = 0;
  size_t len_j = 0;

  if (!*len)
    {
      free(*buf);
      *buf = NULL;
      signal(SIGINT, sigintHandler);
#if USE_GETLINE
      i = getline(buf, &len_j, stdin);
#else
      i = _getline(info, buf, &len_j);
#endif
      if (i > 0)
	{
	  if ((*buf)[i - 1] == '\n')
	    {
	      (*buf)[i - 1] = '\0';
	      i--;
	    }
	  info->linecount_flag = 1;
	  remove_comments(*buf);
	  build_history_list(info, *buf, info->histcount++);
	  {
	    *len = i;
	    info->cmd_buf = buf;
	  }
	}
    }
  return (i);
}

/**
 * get_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
  static char *buff;
  static size_t p, q, len;
  ssize_t i = 0;
  char **buff_p = &(info->arg), *j;

  _putchar(BUFF_FLUSH);
  i = input_buf(info, &buff, &len);
  
  if (i == -1)
    return (-1);

  if (len)
  {
    q = p;
    j = buff + i;

    check_chain(info, buff, &q, p, len);
    while (q < len)
    {
      if (is_chain(info, buff, &q))
        break;
      q++;
    }

    p = q + 1;
    if (p >= len)
    {
      p = len = 0;
      info->cmd_buf_type = CMD_NORM;
    }

    *buff_p = j;
    return (_strlen(j));
  }

  *buff_p = buff;
  return (i);
}

/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
  ssize_t j = 0;

  if (*i)
    return (0);

  j = read(info->readfd, buf, READ_BUFF_SIZE);

  if (j >= 0)
    *i = j;

  return (j);
}

/**
 * _getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(info_t *info __attribute__((unused)), char **ptr, size_t *length)
{
  char *buffer = NULL;
  size_t bufsize = 0;
  ssize_t bytes_read;

  if (ptr == NULL)
    {
      return -1;
    }

  if (*ptr != NULL && length != NULL)
    {
      buffer = *ptr;
      bufsize = *length;
    }

  bytes_read = getline(&buffer, &bufsize, stdin);

  if (bytes_read != -1 && length != NULL)
    {
      *ptr = buffer;
      *length = bufsize;
    }

  return bytes_read;
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
  _puts("\n");
  _puts("$ ");
  _putchar(BUFF_FLUSH);
}
