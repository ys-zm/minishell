/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/28 01:49:19 by fra           #+#    #+#                 */
/*   Updated: 2023/09/16 23:26:04 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell/minishell.h"

char	*get_var_value(t_env **env_vars, char *var_name, int exit_status)
{
	t_env	*env_list;

	env_list = NULL;
	if (ft_strncmp(var_name, "?", 1) == 0)
		return (ft_itoa(exit_status));
	else
	{
		if (env_vars)
			env_list = *env_vars;
		while (env_list)
		{
			if (ft_strncmp(env_list->key, var_name, ft_strlen(var_name)) == 0)
				return (ft_strdup(env_list->value));
			env_list = env_list->next;
		}
		return (ft_strdup(""));
	}
}

char	*expand_vars(char *input, t_env **env_vars, int exit_status)
{
	uint32_t	i;
	uint32_t	end;
	char		*var_name;
	char		*var_value;

	i = 0;
	while (input && input[i])
	{
		if (is_valid_dollar(input, i++) == false)
			continue ;
		end = i;
		while (input[end] && (ft_isalnum(input[end]) \
			|| ft_strchr("?_", input[end])))
			end++;
		var_name = ft_substr(input, i, end - i);
		var_value = get_var_value(env_vars, var_name, exit_status);
		ft_free(var_name);
		if (var_value == NULL)
			return (ft_free(input));
		input = ft_insert_str(input, var_value, i, end);
		i += ft_strlen(var_value) - 1;
		ft_free(var_value);
	}
	return (input);
}

char	*expand_tilde(char *str, t_env **env_vars)
{
	uint32_t	i;
	char		*home_var;

	i = 0;
	while (str && str[i])
	{
		if (ft_isspace(str[i++]) && str[i])
		{
			if (is_valid_symbol(str, i++, '~') && \
				(ft_isspace(str[i]) || (str[i] == '/') || (! str[i])))
			{
				home_var = get_var_value(env_vars, "HOME", 0);
				if (home_var == NULL)
					return (ft_free(str));
				str = ft_insert_str(str, home_var, i, i);
				i += ft_strlen(home_var) - 1;
				ft_free(home_var);
			}
		}
	}
	return (str);
}

char	*expand_pid(char *input)
{
	uint32_t	i;
	char		*char_pid;

	i = 0;
	while (input[i])
	{
		if (is_valid_dollar(input, i++))
		{
			if (input[i] == '$')
			{
				char_pid = ft_itoa(getpid());
				if (char_pid == NULL)
					return (ft_free(input));
				input = ft_insert_str(input, char_pid, i, i + 1);
				i += ft_strlen(char_pid) - 1;
				ft_free(char_pid);
				if (input == NULL)
					return (NULL);
			}
		}
	}
	return (input);
}

t_cmd_status	expander(char **input, t_env **env_vars, int stat, bool check)
{
	char	*tmp_exp;

	tmp_exp = expand_tilde(*input, env_vars);
	if (*input == NULL)
		return (CMD_MEM_ERR);
	tmp_exp = expand_pid(tmp_exp);
	if (tmp_exp == NULL)
		return (CMD_MEM_ERR);
	tmp_exp = expand_vars(tmp_exp, env_vars, stat);
	if (tmp_exp == NULL)
		return (CMD_MEM_ERR);
	if (check && (check_sintax(tmp_exp) == false))
	{
		ft_free(tmp_exp);
		return (CMD_SIN_ERR);
	}
	else
	{
		*input = tmp_exp;
		return (CMD_OK);
	}
}
