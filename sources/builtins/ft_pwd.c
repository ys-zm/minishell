#include "minishell.h"

//pwd wroks with: mkdir a | mkdir a/b | cd a/b | rm -rf ../../a | pwd
//even when you unset PWD and OLD and cwd is supposed to fail.... so how does it work?
char	*ft_get_pwd(t_var *mini)
{
	t_env *env;

	env = *(mini->env_list);
	while (env && ft_strncmp("PWD", env->key, 3))
		env = env->next;
	if (env && !ft_strncmp("PWD", env->key, 3))
		return (env->value);
	return (NULL);
}

//ft_pwd: print working directory
//pass fd!
int	ft_pwd(t_var *mini, char **args, int fd_out)
{
	char	*curr_dir;

	(void)mini;
	if (args[1])
		return (ft_putstr_fd("pwd: bad option: try pwd with no option\n", 2), EXIT_FAILURE);
	curr_dir = getcwd(0, 0);
	if (curr_dir)
	{
		ft_putstr_fd(curr_dir, fd_out);
		ft_putstr_fd("\n", fd_out);
		free(curr_dir);
		return (EXIT_SUCCESS);
	}
	else
	{
		// curr_dir = ft_get_pwd(mini);
		// if (curr_dir)
		// {
		// 	ft_putstr_fd(curr_dir, 1);
		// 	free(curr_dir);
		// 	return (write(STDOUT_FILENO, "\n", 1), EXIT_SUCCESS);
		// }
		write(STDERR_FILENO, "pwd failed\n", 11);
		return (EXIT_FAILURE);
	}
}
