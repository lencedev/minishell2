/*
** EPITECH PROJECT, 2022
** B-PSU-101-MPL-1-1-bsminishell1-owen1.bolling
** File description:
** main
*/

#include "file.h"
#include <curses.h>

static const exec_cmd_t set[5] = {
    {exec_exit, "exit"},
    {exec_cd, "cd"},
    {exec_env, "env"},
    {exec_setenv, "setenv"},
    {exec_unsetenv, "unsetenv"},
};

int handle_signal(int ws)
{
    int a = WTERMSIG(ws);
    char *str = strsignal(a);

    write(1, str, my_strlen(str));

    if (WCOREDUMP(ws)) {
        write(1, "(core dumped)", 13);
        write(1, "\n", 1);
    }
    return 1;
}

int exec_ceo(buff_t *buff, int fd[2])
{
    buff->cmd.fd = fd;
    buff->tab = get_array(my_strdup(buff->cmd.cmd));

    for (int i = 0; i != 5; i++)
        if (my_strcmp(*buff->tab, set[i].name) == 0)
            return set[i].function(buff);
    return (exec_pipes(buff, fd) != 0) ? handle_signal(buff->ws) : 0;
}

int checker(char *str)
{
    char **array = get_array(my_strdup(str));

    return (*array) ? 1 : 0;
}

int worldwild_ceo(buff_t *buff)
{
    char **parsed;
    int fd[2] = {STDIN_FILENO, STDOUT_FILENO};
    buff->cmd.cmd = my_strdup(buff->line);

    if (!(count_parse(buff->cmd.cmd, ';') > 1))
        if (checker(buff->cmd.cmd))
            return buff->value = pipes_manager(buff, fd);
        else
            return buff->value;

    parsed = parsing_line(buff->cmd.cmd, ';');
    for (; *parsed; *parsed++) {
        buff->cmd.cmd = my_strdup(*parsed);
        if (*buff->cmd.cmd)
            buff->value = pipes_manager(buff, fd);
    }
    return buff->value;
}

int main(int ac, char **av, char **env)
{
    buff_t buff = init_buff(env);

    while (1) {
        if (isatty(0) && getcwd(buff.cwd, sizeof(buff.cwd)) != NULL)
            display_pwd(&buff, buff.user);

        my_getline(&buff);

        if (buff.line != NULL)
            buff.value = worldwild_ceo(&buff);
    }
    return buff.value;
}
