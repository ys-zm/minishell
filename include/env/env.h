/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/01 02:17:18 by fra           #+#    #+#                 */
/*   Updated: 2023/07/01 02:17:32 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

// env/utils.c

int		ft_find_first_equals(char *env);

bool	ft_key_rules(char c, int index);

int		ft_check_key(char *key, char *cmd);

int     ft_find_data_if_no_pos(t_var *mini, char *envp, char **key, char **value);

t_env	*ft_create_node(t_var *mini, char *envp, int pos);

// env/env_parsing.c

void	ft_print_array(char **arr);

void	ft_update_shell(t_var *mini, t_env **env_list);

void	ft_free_prev(t_env *head);

t_env	*ft_envp_node(t_var *mini, char *envp);

void	make_env_list(char **envp, t_var *mini);

#endif