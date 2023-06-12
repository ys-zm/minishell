#include "minishell.h"

//ft_pwd: print working directory
int    ft_pwd(int fd_out)
{
    char    *curr_dir;

    (void)fd_out;
    curr_dir = getcwd(0, 0);
    if (curr_dir)
    {
        ft_putstr_fd(curr_dir, 1);
        write(1, "\n", 1);
        free(curr_dir);
        return (EXIT_SUCCESS);
    }
    else
        return (EXIT_FAILURE);
}