#include "minishell.h"

void    child_error_handler()
{
    if (errno == 8)
    {
        g_exit_code = 127;
    }
}