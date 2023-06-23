#include "minishell.h"

void	ft_increment_shlvl(t_var *mini)
{
	t_env	*env_list;
	int		value;

	env_list = *(mini->env_list);
	while (env_list)
	{
		if (!ft_strcmp(env_list->key, "SHLVL"))
			break ;
		env_list = env_list->next;
	}
	if (env_list)
	{
		value = ft_atoi(env_list->value);
		value += 1;
		free(env_list->value);
		env_list->value = ft_itoa(value);
	}
}

void	ft_set_shlvl(t_var *mini, char *cmd_name)
{
	if (cmd_name && !ft_strcmp("./minishell", cmd_name))
	{
		if (ft_check_if_key_exists(*(mini->env_list), "SHLVL"))
			ft_increment_shlvl(mini);
		else
			ft_add_node(mini->env_list, ft_new_node("SHLVL", "1"));
	}
}