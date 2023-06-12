#include "minishell.h"

void    child_error_handler()
{
    if (errno == 8)
    {
        global_exit_code = 127;
    }
}