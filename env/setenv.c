/*
** EPITECH PROJECT, 2022
** B-PSU-101-MPL-1-1-minishell1-owen1.bolling
** File description:
** setenv
*/

#include "file.h"

int check_first_char(char *chilling, char c)
{
    for (; *chilling; *chilling++) {
        if (*chilling == c)
            return 1;
    }
    return 0;
}

int check_setenv_value(char *str_1)
{
    char *bing = "=?/@[\\]^`{}~*0123456789";
    char *chilling = "~{}^[\\@?=:/-,+*";

    for (int i = 0; str_1[i] != '\0'; i++) {
        if (check_first_char(chilling, str_1[i])) {
            write(1, "setenv: Variable name must contain ", 35);
            write(1, "alphanumeric characters.\n", 25);
            return 0;
        }
    }
    return 1;
}

int check_setenv_name(char *str_1)
{
    char *bing = "=?/@[\\]^`{}~*0123456789";
    char *chilling = "~{}^[\\@?=:/-,+*";

    if (check_first_char(bing, str_1[0])) {
        write(1, "setenv: Variable name must begin with a letter.\n", 48);
        return 0;
    }
    for (int i = 0; str_1[i] != '\0'; i++) {
        if (check_first_char(chilling, str_1[i])) {
            write(1, "setenv: Variable name must contain ", 35);
            write(1, "alphanumeric characters.\n", 25);
            return 0;
        }
    }
    return 1;
}

int edit_env(buff_t *buff)
{
    if (buff->tab[2]) {
        edit_list_value(&buff->list_env, buff->tab[1], buff->tab[2]);
        return 1;
    }
    edit_list_value(&buff->list_env, buff->tab[1], "");
    return 0;
}

int exec_setenv(buff_t *buff)
{
    if (!buff->tab[1])
        return print_env(*buff);

    char *arg = my_strcat(buff->tab[1], "=");

    if (check_nb_args(buff->tab, 3)) {
        write(buff->cmd.fd[1], "setenv: Too many arguments.\n", 28);
        return 0;
    }
    if (check_setenv_name(buff->tab[1]))
        if (check_list_name(buff->list_env, buff->tab[1]))
            return edit_env(buff);
        return create_env(buff, arg);
    return 0;
}
