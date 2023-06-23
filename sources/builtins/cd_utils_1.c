#include "minishell.h"

char	*ft_remove_lastdir(t_var *mini, char *old_path)
{
	int	len;
	int	i;
	char	*new_path;

	len = ft_strlen(old_path);
	i = len - 1;
	if (old_path[i] == '/')
		i--;
	while (i >= 0)
	{
		if (old_path[i] == '/')
			break ;
		i--;
	}
	new_path = ft_substr(old_path, 0, i + 1);
	if (!new_path)
		malloc_protect(mini);
	return (new_path);
}

char   	*ft_get_home(t_var *mini)
{
	t_env	*env;

	env = *(mini->env_list);
	while (env && ft_strncmp(env->key, "HOME", 4))
	{
        if (env && !ft_strncmp(env->key, "HOME", 4))
            return (env->value); 
        env = env->next;
    }
	return (NULL);
}

t_env	*ft_search_env_var(t_env **env_list, char *which_env)
{
	t_env	*env;

	env = *env_list;
	while (env)
	{
		if (!ft_strncmp(which_env, env->key, ft_strlen(which_env)))
			break ;
		env = env->next;
	}
	return (env);
}

void	ft_update_env_var(t_env **env_list, char *which_env, char *new_env)
{
	t_env	*env_var;

	env_var = ft_search_env_var(env_list, which_env);
	if (env_var)
	{
		free(env_var->value);
		env_var->value = ft_strdup(new_env); //malloc being freed was not appointed
	}
}

bool	ft_check_for_tilde(char **args)
{
	if (count_args(args) == 2 && !ft_strncmp("~", args[1], 1))
		return (true);
	return (false);
}

char	*ft_replace_tilde(t_var *mini, char *str)
{
	size_t	len;
	char	*home_path;
	char	*new_path;
	char	*temp;

	len = ft_strlen(str) - 2;
	home_path = ft_get_home(mini);
	temp = ft_substr(str, 2, len);
	if (!temp)
		malloc_protect(mini);
	new_path = ft_trip_join(home_path, "/", temp);
	free(temp);
	return (new_path);
}	

int	ft_cd_to_homedir(t_var *mini)
{
	char	*new_path;
	
	new_path = ft_get_home(mini);
	if (!new_path)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (EXIT_FAILURE);
	}
	if (!chdir(new_path))
		return (EXIT_SUCCESS);
	else
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(new_path, 2);
		return (ft_putstr_fd(": No such file or directory\n", 2), EXIT_FAILURE);
    }
}

int	ft_cd_to_oldpwd(t_var *mini)
{
	char	*old_pwd;
	t_env	*env;

	env = *(mini->env_list);
	while (env && ft_strncmp(env->key, "OLDPWD", 6))
		env = env->next;
	if (env && !ft_strncmp(env->key, "OLDPWD", 6))
		old_pwd = env->value;
	else
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set", 2);
		return (EXIT_FAILURE);
	}
	if (!chdir(old_pwd))
		return (EXIT_SUCCESS);
	else
	{
		write(STDERR_FILENO, "1232", 4);
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(old_pwd, 2);
		return (ft_putstr_fd(": No such file or directory\n", 2), EXIT_FAILURE);
    }
}

int	ft_count_directories(char *arg)
{
	int	count;
	int	flag;

	flag = 1;
	count = 0;
	while (*arg == '/')
		arg++;
	while (arg && *arg)
	{
		if (*arg != '/')
			flag = 1;
		if (*arg == '/' && flag == 1)
		{
			flag = 0;
			count++;
		}
		arg++;
	}
	if (flag == 1 && !*arg)
		count++;
	if (!count)
		return (1);
	return (count);

}