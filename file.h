/*
** EPITECH PROJECT, 2022
** minishell1
** File description:
** my
*/

#ifndef FILE_H_
    #define FILE_H_

    #include <stdarg.h>
    #include <unistd.h>
    #include <stdio.h>
    #include <string.h>
    #include <sys/types.h>
    #include <sys/wait.h>
    #include <stdlib.h>
    #include "tools.h"
    #include <sys/stat.h>
    #include <fcntl.h>
    #include <errno.h>

    #define RED 0
    #define GREEN 1
    #define YELLOW 2
    #define BLUE 3
    #define CYAN 4
    #define BOLD_WHITE 5
    #define L_RED 6
    #define L_GREEN 7
    #define L_YELLOW 8
    #define L_BLUE 9
    #define L_PINK 10
    #define L_CYAN 11

typedef struct list_s {
    char *name;
    char *value;
    struct list_s *next;
} list_t;

typedef struct colors_t {
    char *color_1;
    char *color_2;
} colors_t;

typedef struct cmd_s {
    int *fd;
    char *cmd;
} cmd_t;

typedef struct path_s {
    int nb_folders;
    char **parsed;
} path_t;

typedef struct buff_s {
    char **env;
    list_t *list_env;
    cmd_t cmd;
    char **tab;
    char *line;
    char *user;
    char *pwd;
    char cwd[1000];
    ssize_t len;
    int value;
    int ws;
    path_t path;
} buff_t;

typedef struct exec_cmd_s {
    int (*function)(buff_t *);
    char *name;
} exec_cmd_t;

void ls_option_stat(char **av, char *str);

char **parsing_path(char *path);
char *find_cmd(buff_t *buff);

char *parse_pwd(char *env, char *str, int size);
void exit_process(int value);

void display_pwd(buff_t *buff, char *user);
int display_no_such_cd(buff_t *buff);
void display_too_many_args(void);
void my_getline(buff_t *buff);

list_t *find_env_list(list_t *env, const char *str);
void create_node_at_back(list_t **env, const char *str);
void init_env(buff_t *buff);
void set_env(buff_t *buff);
int unset_env(list_t **env, const char *s);
int len_until_char(const char *str, char c);
int print_env(buff_t buff);
void edit_list_name(list_t **env, const char *str, const char *name);
void edit_list_value(list_t **env, const char *str, const char *value);
int check_list_name(list_t *env, const char *name);
int create_env(buff_t *buff, char *arg);
int edit_env(buff_t *buff);
int is_env(char *tab);

int count_words(char *line);
char **get_array(char *line);
int count_parse(char *str, char obj);
char *parse_env_path(char **env, char *str, int size);

int exec_path(buff_t *buff);
int exec_cd(buff_t *buff);
int display_cd_much_args(buff_t *buff);
int exec_env(buff_t *buff);
int exec_setenv(buff_t *buff);
int exec_unsetenv(buff_t *buff);

int check_nb_args(char **env, int nb);
int add_oldpwd(list_t **env);

buff_t init_buff(char **env);

int display_error(char *tab, int *error_code);
int check_slash(char *str);

char **parsing_line(char *line, char obj);
void split_line(char ***tab, char *line, char obj);
int exec_exit(buff_t *buff);
int exec_null(buff_t *buff);
int exec_ceo(buff_t *buff, int fd[2]);
int executer(buff_t *buff);
int exec_pipes(buff_t *buff, int fd[2]);
int pipes_manager(buff_t *buff, int fd[2]);
int parsing_ceo(buff_t *buff, int fd[2]);
int count_multi_parses(char *str, char *obj);
int count_words_custom(char *line, char *obj);
char **get_array_custom(char *line, char *obj);
void close_fd(int *fd);

char *parse_output(char **buff);
char *parse_cmd(char **buff);

int parsing_redirect(buff_t *buff, int fd[2]);

int redirect_input_manager(buff_t *buff, int fd[2]);
int redirect_double_input_manager(buff_t *buff, int fd[2]);
int redirect_output_manager(buff_t *buff, int fd[2]);
int redirect_double_output_manager(buff_t *buff, int fd[2]);

#endif /* !FILE_H_ */
