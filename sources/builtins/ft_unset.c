#include "minishell.h"

int	ft_del_node(t_var *mini, char *key)
{
	t_env	*env_list;
	t_env	*prev;
	t_env	*next;
	t_env	*curr;

	env_list = *(mini->env_list);
	curr = env_list;
	prev = NULL;
	if (env_list->next)
		next = env_list->next;
	if (curr->key && !ft_strcmp(curr->key, key))
	{
		free(curr);
		*(mini->env_list) = next; //can this seg fault if it is null
	}
	else
	{
		while (curr)
		{
			if (!ft_strcmp(curr->key, key))
				break ;
		prev = curr;
		curr = curr->next;
		if (curr)
			next = curr->next;
		}
	}
	if (curr && !ft_strcmp(curr->key, key))
	{
		prev->next = next; //segfault bait
		free(curr->key);
		free(curr->value);
		free(curr); //its a struct
	}
	return (EXIT_FAILURE);
}

//ft_unset: remove env variable from list
//if its the head, set new head
//if not valid key
int	ft_unset(t_var *mini, char **args, int fd_out)
{
	int	i;
	t_env	*env;

	i = 1;
	env = *(mini->env_list);
	(void)fd_out;
	if (!args || !env)
		return (EXIT_SUCCESS);
	while (args && args[i])
	{
		ft_check_key(args[i]);
		if (ft_del_node(mini, args[i]))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
