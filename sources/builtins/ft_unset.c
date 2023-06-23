#include "minishell.h"

void	ft_del_node(t_env **env_list, char *key)
{
	t_env	*curr;
	t_env	*prev;

	if (!env_list)
		return ;

	curr = *env_list;
	prev = NULL;
	while (curr)
	{
		if (!ft_strncmp(curr->key, key, ft_strlen(curr->key)))
		{
			if (!prev)
				*env_list = curr->next;
			else
				prev->next = curr->next;
			free(curr->key);
			free(curr->value);
			free(curr);
			return ;
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
			
	}
}

//ft_unset: remove env variable from list
//if its the head, set new head
//if not valid key
int	ft_unset(t_var *mini, char **args)
{
	int	i;
	t_env	*env;

	i = 1;
	if (mini->env_list)
		env = *(mini->env_list);
	ft_print_array(args);
	if (!args || !env)
		return (EXIT_SUCCESS);
	while (args && args[i])
	{
		if (!ft_check_key(args[i]))
			ft_del_node(mini->env_list, args[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
