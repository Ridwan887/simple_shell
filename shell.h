#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passdata - contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguements
 * @argv:an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
 */
typedef struct passdata
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

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} data_d;

#define DATA_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(data_d *);
} builtin_table;


/* toem_shell_core.c */
int hsh(info_t *info, char **av);
int find_builtin(info_t *info);
void find_cmd(info_t *info);
void fork_cmd(info_t *info);

/* toem_getPath_handling.c */
int isExecutableCommand(data_d *data, char *path);
char *duplicateCharacters(char *pathStr, int start, int stop);
char *findCommandPath(data_d *data, char *pathStr, char *command);

/* loophsh.c */
int loophsh(char **);

/* toem_myerrors_output.c */
void _mysterious_puts(char *string)
int _secret_putchar(char character);
int _write_to_fd(char character, int file_descriptor);
int _print_to_fd(char *string, int file_descriptor);
int str_length(char *str);
int str_compare(char *str1, char *str2);
char *starts_with_str(const char *haystack, const char *needle);
char *string_concat(char *destination, char *source);

/* toem_puts_strings.c */
char *copy_string(char *destination, char *source);
char *_strdup(const char *);
void print_string(char *str);
int print_character(char c);

/* toem_strings_exits.c */
char *_blend_messages(char *secret, char *covert, int cloak);
char *_find_secret(char *classified, char item);
char *_hide_ciphertext(char *hideout, char *stealth, int cloak);

/* toem_str_tokens.c */
char **split_string(char *input_string, char *delimiter_string);
char **split_string2(char *input_string, char delimiter);

/* toem_allocate_memsets.c */
char *fillMemory(char *destination, char byte, unsigned int size);
void *reallocateMemory(void *previousPtr, unsigned int oldSize, unsigned int newSize);
void freeArrayOfStrings(char **strArray);

/* toem_frees_memory.c */
int bfree(void **);

/* toem_a_prompt.c */
int communicative(data_d *);
int is_delimiterChars(char, char *);
int _byte(int);
int a_prompt(char *);

/* toem_myerrors_output.c */
int _decode_secret(char *covert);
void obscure_message(info_t *info, char *cipher);
int cipher_code(int message, int fd);
char *encode_message(long int message, int base, int flags);
void conceal_comments(char *secret);

/* toem_*shell_exits.c */
int exit_shell(data_d*)
int change_directory(data_d*)
int help_command(data_d*)

/* toem_builtin_alias.c */
int _history_echo(data_d *);
int _covert_operation_alias(data_d *);

/*toem_getLine_inputs.c */
ssize_t deep_cover(data_d *data, char **buf, size_t *len);
int _secret_message(data_d *data, char **ptr, size_t *length);
void stealthHandler(__attribute__((unused))int sig_num);

/* toem_command_getinform.c */
void initializeData(data_d *data);
void initData(data_d *data, char **argumentsVector);
void releaseData(data_d *data, int freeAll);

/* toem_myenv_functions.c */
char _myclassified(data_d *, const char *);
int *_get_secre(data_d *);
int _create_secret(data_d *);
int _destroy_secret(data_d *);
int create_undercover_list(data_d *);

/* toem_mygetEnv_functions.c */
char **getUnthinkableEnv(data_d *data);
int removeFromEnv(data_d *data, char *varName);
int setUnthinkableEnv(data_d *data, char *varName, char *varValue);

/* toem_handle_historyfunctions.c */
char *fetchHistoryFile(data_d *data);
int saveHistory(data_d *data);
int loadHistory(data_d *data);
int appendHistoryEntry(data_d *data, char *buffer, int lineCount);
int renumberHistory(data_d *data);

/* toem_getnode_lists.c */
list_t *prependToList(list_t **start, const char *text, int index);
list_t *appendToTail(list_t **start, const char *text, int index);
size_t printStringList(const list_t *list);
int removeNodeAtIndex(list_t **start, unsigned int index);
void freeStringList(list_t **start);

/* the_nodelists_func.c */
size_t determineListLength(const list_t *node);
char **convertListToStrings(list_t *list);
size_t displayList(const list_t *node);
list_t *findNodeWithPrefix(list_t *node, char *prefix, char character);
ssize_t getNodeIndex(list_t *head, list_t *node);

/* the_chain_processing */
int is_chain_delimiter(data_d *data, char *buf, size_t *p);
void check_continue_chain(data_d *data, char *buf, size_t *p, size_t i, size_t len);
int replace_aliases(data_d *data);
int replace_variables(data_d *data);
int replace_string(char **old, char *new);

#endif
