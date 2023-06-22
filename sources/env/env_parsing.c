#include "minishell.h"

void	ft_print_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		ft_putstr_fd(arr[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
}

// NB this function must resturn NULL/0/... in case of failure
void    make_env_list(char **envp, t_var *mini)
{
	t_env	*new_node = NULL;
	t_env   *first;
	t_env   *env_list;
	// char    **arr = NULL;
	int i;
	i = 0;

	env_list = ft_envp_node(mini, envp[i++]); // if it is null it could also be because the key does not fit the right format
	if (!env_list)
		return ;
	mini->env_list = malloc(sizeof(t_env *) * 1);
	if (!mini->env_list)
		return ;
	first = env_list;
	while (envp && envp[i])
	{
		new_node = ft_envp_node(mini, envp[i]);
		if (!new_node)
			malloc_protect(mini);
		if (i > 5)
			break ;
		env_list->next = new_node;
		env_list = env_list->next;
		i++;
	}
	*(mini->env_list) = first;
	// arr = ft_list_to_arr(mini, *(mini->env_list));
	// ft_print_array(arr);
	// exit(0);
}
