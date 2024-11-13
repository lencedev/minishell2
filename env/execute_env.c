/*
** EPITECH PROJECT, 2022
** B-PSU-101-MPL-1-1-minishell1-owen1.bolling
** File description:
** execute_env
*/

#include "file.h"

int is_env(char *tab)
{
    if (my_strncmp(tab, "env", 4) == 0
    || my_strncmp(tab, "setenv", 7) == 0
    || my_strncmp(tab, "unsetenv", 9) == 0)
        return 1;
    else
        return 0;
}

int check_nb_args(char **env, int nb)
{
    int i;
    for (i = 0; env[i]; i++);
    return (i > nb) ? 1 : 0;
}

int create_env(buff_t *buff, char *arg)
{
    if (buff->tab[2]) {
        create_node_at_back(&buff->list_env, my_strcat(arg, buff->tab[2]));
        return 1;
    }
    create_node_at_back(&buff->list_env, arg);
    return 0;
}

int exec_env(buff_t *buff)
{
    if (my_strncmp(*buff->tab, "env", 4) == 0)
        return print_env(*buff);
    if (my_strncmp(*buff->tab, "setenv", 7) == 0)
        return exec_setenv(buff);
    if (my_strncmp(*buff->tab, "unsetenv", 9) == 0)
        return exec_unsetenv(buff);
    return 1;
}
