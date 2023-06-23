/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_env.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/23 14:30:00 by yzaim         #+#    #+#                 */
/*   Updated: 2023/06/23 16:49:11 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_env(char **arr, int fd_out)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		ft_putstr_fd(arr[i], fd_out); // into fd
		ft_putstr_fd("\n", fd_out);
		i++;
	}
}

size_t	ft_list_size_to_print(t_env *env_list)
{
	size_t	count;

	count = 0;
	while (env_list)
	{
		if (env_list->value)
			count++;
		env_list = env_list->next;
	}
	printf("count: %zu\n", count);
	return (count);
}

char	**ft_list_to_arr(t_var *mini, t_env *env_list)
{
	size_t	i;
	size_t	size;
	char	**arr;

	i = 0; 
	size = ft_list_size_to_print(env_list);
	if (!size)
		return (NULL);
	arr = malloc(sizeof(char *) * (size + 1));
	if (!arr)
		malloc_protect(mini);
	while (i < size)
	{
		printf("keys: %s\n", env_list->key);
		if (env_list->value)
			arr[i++] = ft_trip_join(env_list->key, "=", env_list->value);
		env_list = env_list->next;
	}
	arr[i] = NULL;
	ft_print_array(arr);
	return (arr);
}

//ft_env: print env variable char array
int	ft_env(t_var *mini, int fd_out)
{
	printf("first key: %s\n", (*mini->env_list)->key);
	mini->env_arr = ft_list_to_arr(mini, *mini->env_list);
	printf("\n\n\n");
	if (!mini->env_arr)
		return (EXIT_FAILURE);
	ft_print_env(mini->env_arr, fd_out);
	return (EXIT_SUCCESS);
}
