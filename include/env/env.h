/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/01 02:17:18 by fra           #+#    #+#                 */
/*   Updated: 2023/07/11 16:54:54 by faru          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

// env/utils.c
int		ft_find_first_equals(char *env);

bool	ft_key_rules(char c, int index);

int		ft_check_key(char *key, char *cmd);

int		ft_find_data_if_no_pos(t_var *mini, char *envp, char **key, char **v);

t_env	*ft_create_node(t_var *mini, char *envp, int pos);

// env/env_parsing.c
void	ft_print_array(char **arr);

void	ft_free_prev(t_env *head);

void	ft_update_shell(t_env **env_list);

t_env	*ft_envp_node(t_var *mini, char *envp);

void	make_env_list(char **envp, t_var *mini);

#endif
