/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/28 01:49:19 by fra           #+#    #+#                 */
/*   Updated: 2023/06/26 14:59:47 by faru          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var_value(t_env *env_vars, char *var_name)
{
	char	*var_value;

	if (var_name == NULL)
		return (NULL);
	else if (ft_strncmp(var_name, "?", 1) == 0)
		var_value = ft_itoa(g_exit_code);
	else
	{
		var_value = NULL;
		while (env_vars)
		{
			if (ft_strncmp(env_vars->key, var_name, ft_strlen(var_name)) == 0)
			{
				var_value = ft_strdup(env_vars->value);
				break ;
			}
			env_vars = env_vars->next;
		}
		if (var_value == NULL)
			var_value = ft_strdup("");
	}
	ft_free(var_name);
	return (var_value);
}

char	*expand_vars(char *input, t_env *env_vars)
{
	uint32_t	i;
	uint32_t	end;
	char		*var_name;
	char		*var_value;

	i = 0;
	while (input[i])
	{
		if (is_valid_dollar(input, i++) == false)
			continue ;
		end = i;
		while (ft_isalpha(input[end]) || (input[end] == '?'))
			end++;
		var_name = ft_substr(input, i, end - i);
		var_value = get_var_value(env_vars, var_name);
		if (var_value == NULL)
			return (ft_free(input));
		input = ft_insert_str(input, var_value, i, end);
		i += ft_strlen(var_value) - 1;
		ft_free(var_value);
		if (input == NULL)
			return (NULL);
	}
	return (input);
}

char	*expand_tilde(char *str, t_env *env_vars)
{
	uint32_t	i;
	char		*home_var;

	i = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]) && str[i + 1])
		{
			i++;
			if (is_valid_symbol(str, i++, '~'))
			{
				if (ft_isspace(str[i]) || (str[i] == '/') || (! str[i]))
				{
					home_var = get_var_value(env_vars, "HOME");
					str = ft_insert_str(str, home_var, i, i);
					i += ft_strlen(home_var) - 1;
					if (str == NULL)
						return (NULL);
				}
			}
		}
		else
			i++;
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
		if (is_valid_symbol(input, i++, '$'))
		{
			if (is_valid_symbol(input, i, '$'))
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

char	*expander(char *input, t_env *env_vars)
{
	char	*tilde_exp;
	char	*pid_exp;
	char	*var_exp;

	tilde_exp = expand_tilde(input, env_vars);
	if (tilde_exp == NULL)
		return (NULL);
	pid_exp = expand_pid(tilde_exp);
	if (pid_exp == NULL)
		return (NULL);
	var_exp = expand_vars(pid_exp, env_vars);
	if (var_exp == NULL)
		return (NULL);
	else
		return (var_exp);
}
