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

void	ft_update_shell(t_env **env_list)
{
	t_env	*env;

	env = *env_list;
	while (env)
	{
		if (!ft_strncmp("SHELL", env->key, 5))
		{
			free(env->value);
			env->value = getcwd(0, 0);
			return ;
		}
		env = env->next;
	}
}

void	ft_free_prev(t_env* head)
{
	t_env	*tmp;

	tmp = NULL;
	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}

// NB this function must resturn NULL/0/... in case of failure
void	make_env_list(char **envp, t_var *mini)
{
	t_env	*head;
	t_env	*node;
	int		i;

	i = 1;
	ft_print_array(envp);
	mini->env_list = ft_calloc(sizeof(t_env *), 1);
	if (!mini->env_list)
		malloc_protect(mini);
	head = ft_envp_node(mini, envp[0]);
	if (!head)
		malloc_protect(mini);
	node = head;
	printf("nodes: %s\n", node->key);
	while (envp[i])
	{
		node->next = ft_envp_node(mini, envp[i]);
		if (!node->next)
		{
			ft_free_prev(head);
			malloc_protect(mini);
		}
		node = node->next;
		printf("nodes: %s\n", node->key);
		i++;
	}
	*(mini->env_list) = head;
	// ft_update_shell(mini->env_list);
}
