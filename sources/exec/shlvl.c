/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shlvl.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: yzaim <marvin@codam.nl>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/26 14:05:32 by yzaim         #+#    #+#                 */
/*   Updated: 2023/06/26 14:05:49 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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

//split this function :o
//how can i deal with this when you are in a different directory
bool	ft_check_if_minishell(t_var *mini, char *cmd_name)
{
	char	*cwd;
	char	**shell_loc;
	char	**cwd_arr;
	char	**cmd_arr;
	int		i = 0;
	int		j = 0;
	int		j_count = 0;
	int		i_count = 0;
	bool	ret = 0;
	int		curr_cwd_arr = 0;
	
	cwd = getcwd(0, 0);
	if (!cwd)
	{
		printf("ERROR!\n");
	}
	cwd_arr = ft_split(cwd, '/', 0);
	if (!cwd_arr)
		malloc_protect(mini);
	free(cwd);
	cmd_arr = ft_split(cmd_name, '/', 0);
	if (!cmd_arr)
		malloc_protect(mini);
	shell_loc = ft_split(mini->shell_loc, '/', 0);
	if (!shell_loc)
		malloc_protect(mini);
	// exit(0);
	while (cwd_arr[i]  && shell_loc[i] && !ft_strncmp(cwd_arr[i], shell_loc[i], ft_strlen(shell_loc[i])))
		i++;
	curr_cwd_arr = count_args(cwd_arr);
	i_count = curr_cwd_arr - i;
	while (cmd_arr[j])
	{
		if (!ft_strncmp("..", cmd_arr[j], 2))
		{
			j++;
			j_count++;
		}
		else if (!ft_strncmp(".", cmd_arr[j], 1))
			j++;
		else
			break ;
	}
	if (!ft_strncmp("minishell", cmd_arr[j], 9) && j_count == i_count)
		ret = 1;
	ft_free_strings(cwd_arr);
	ft_free_strings(cmd_arr);
	ft_free_strings(shell_loc);
	return (ret);
}

// how to increment shlvl
//wierd crash when i do ../minishell twice

void	ft_set_shlvl(t_var *mini, char *cmd_name)
{
	if (cmd_name && ft_check_if_minishell(mini, cmd_name))
	{
		if (ft_check_if_key_exists(*(mini->env_list), "SHLVL"))
			ft_increment_shlvl(mini);
		else
			ft_add_node(mini->env_list, ft_new_node("SHLVL", "1"));
	}
}

//previuos version
// void	ft_set_shlvl(t_var *mini, char *cmd_name)
// {
// 	if (cmd_name && !ft_strcmp("./minishell", cmd_name))
// 	{
// 		if (ft_check_if_key_exists(*(mini->env_list), "SHLVL"))
// 			ft_increment_shlvl(mini);
// 		else
// 			ft_add_node(mini->env_list, ft_new_node("SHLVL", "1"));
// 	}
// }