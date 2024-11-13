/*
** EPITECH PROJECT, 2022
** B-PSU-210-MPL-2-1-minishell2-owen1.bolling
** File description:
** pipes
*/

#include "file.h"

void close_fd(int *fd)
{
    if (fd[0] != STDIN_FILENO)
        close(fd[0]);
    if (fd[1] != STDOUT_FILENO)
        close(fd[1]);
    return;
}

int exec_pipes(buff_t *buff, int fd[2])
{
    char *bing = find_cmd(buff);
    pid_t pid = fork();

    if (pid == 0) {
        dup2(fd[0], STDIN_FILENO);
        dup2(fd[1], STDOUT_FILENO);
        if (!pid && execve(bing, buff->tab, buff->env) == -1)
            exit(buff->value = display_error(bing, &errno));
    }
    if (pid && waitpid(pid, &buff->ws, 0) == -1)
        exit(84);
    close_fd(fd);
    return 0;
}

int pipes_manager(buff_t *buff, int fd[2])
{
    if (!(count_parse(buff->cmd.cmd, '|') > 1))
        return buff->value = parsing_redirect(buff, fd);
    char **parsed = NULL;

    pipe(fd);
    parsed = parsing_line(buff->cmd.cmd, '|');
    if (parsed[0]) {
        buff->cmd.cmd = my_strdup(parsed[0]);
        buff->value = parsing_redirect(buff, (int [2]) {STDIN_FILENO, fd[1]});
    }
    if (parsed[1]) {
        buff->cmd.cmd = my_strdup(parsed[1]);
        buff->value = parsing_redirect(buff, (int [2]) {fd[0], STDOUT_FILENO});
    }
    return buff->value;
}
