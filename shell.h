/* shell.h */

#ifndef SHELL_H
#define SHELL_H

/* Libraries */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>  /* Corrected header name */

/*read/write buffers*/
#define READ_BUFF_SIZE 1024
#define WRITE_BUFF_SIZE 1024
#define BUFF_FLUSH -1

/*convert_number*/
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/*system getline()*/
#define USE_GETLINE 0
#define USE_STRTOK 0

/*command chain*/
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/*path and max*/
#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;
/**
 * struct liststr - singly linked list
 * @num: integer field representing a number
 * @str: character pointer field representing a string
 * @next: points to the next node in singly linked list
 */
struct liststr
{
  char **items;
    int count;
} list_t;

/**
 * struct passinfo - holds pseudo-arguments that can be passed into a function,
 * ensuring a consistent function pointer prototype
 * @arg: string generated from the getline function, which contains arguments
 * @argv: an array of strings that are generated from the arg string
 * @path: string representing the path for the current command
 * @argc: count of errors that have occurred
 * @line_count:count of errors that have occurred
 * @err_num: code used for the exit() function
 * @linecount_flag: indicates if the current line of input should be counted
 * @fname: filename of the program
 * @env: linked list representing a local copy of the environ variable.
 * @environ: custom modified copy of the environ variable obtained from the linked list env
 * @history: points to the history node
 * @alias: points to the alias node
 * @env_changed: indicates if the environ variable has been modified
 * @status: holds the return status of the last executed command
 *@cmd_buf: address of a pointer to the command buffer, used when chaining commands
 * @cmd_buf_type: type of command chaining, such as CMD_type ||, CMD_type &&, or CMD_type ;
 * @readfd: file descriptor from which line input is read
 * @histcount: history line number count
*/
typedef struct passinfo
{
  char *arg;
  char **argv;
  char *path;
  int argc;
  unsigned int line_count;
  int err_num;
  int linecount_flag;
  char *fname;
  list_t *env;
  list_t *history;
  list_t *alias;
  char **environ;
  int env_changed;
  int status;
  char **cmd_buf;
  int cmd_buf_type;
  int readfd;
  int histcount;
  int jute;
  char *cmd;
} info_t;

#define INFO_INIT {NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL,0, 0, 0}

/**
 * struct builtin - structure for built-in commands
 * @type: flag representing the built-in command
 * @func: function for the built-in command
 */
typedef struct builtin
{
  char *type;
  int (*func)(info_t *);
} builtin_t;

/* function prototype */
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);
int loophsh(char **);
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char c);
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);
char **strtow(char *, char *);
char **strtow2(char *, char);
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);
int bfree(void **);
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);
int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);
int _myhistory(info_t *);
int _myalias(info_t *);
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);
const char **list_to_array(list_t *list);
int wordnos(char *s);

#endif /* SHELL_H */
