#include "minishell.h"

//Uilts for Adding to Env_List

int	ft_find_first_equals(char *env)
{
	int	i;

	i = 0;
	while (env && env[i] && env[i] != '=')
		i++;
	if (env[i] == '\0')
		return (0);
	return (i);
}

int	ft_check_key(char *key)
{
	int	i;

	i = 0;
	if (key && key[0])
	{
		if (ft_isalpha(key[0]) == 0 && key[0] != '_')
		{
			ft_putstr_fd("minishell: export: '", 2);
			ft_putstr_fd(key, 2);
			ft_putstr_fd("' : not a valid identifier\n", 2);
			return (EXIT_FAILURE);
		}
	}
	while (key && key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
		{
			ft_putstr_fd("minishell: export: '", 2);
			ft_putstr_fd(key, 2);
			ft_putstr_fd("' : not a valid identifier\n", 2);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

t_env	*ft_envp_node(t_var *mini, char *envp)
{
	int	pos;
	char	*key = NULL;
	char	*value = NULL;
	t_env	*new_node = NULL;

	pos = ft_find_first_equals(envp);
	if (pos)
	{
		key = ft_substr(envp, 0, pos);
		if (!key)
			malloc_protect(mini);
		if (ft_check_key(key))
			return (NULL);
		value = ft_substr(envp, pos + 1, ft_strlen(envp));
		if (!value)
		{
			free(key);
			malloc_protect(mini);
		}
	}
	else
	{
		key = ft_substr(envp, 0, ft_strlen(envp));
		if (!key)
			malloc_protect(mini);
		if (ft_check_key(key))
			return (NULL);
		value = NULL;
	}
	new_node = ft_new_node(key, value);
	return (new_node);
}
