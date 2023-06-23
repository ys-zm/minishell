/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_vars.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/28 01:49:19 by fra           #+#    #+#                 */
/*   Updated: 2023/06/23 14:42:57 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var_value(t_env *env_vars, char *var_name)
{
	while (env_vars)
	{
		if (ft_strncmp(env_vars->key, var_name, ft_strlen(var_name)) == 0)
			return (env_vars->value);
		env_vars = env_vars->next;
	}
	return (NULL);
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
		if (is_valid_dollar(input, i++))
		{
			end = i;
			while (input[end] && (! ft_isspace(input[end])) && (input[end] != '|') && (! is_quote(input[end])) && (input[end] != '='))//	ft_strchr(input[i], " |'\"=")
			{
				end++;
				if (input[end - 1] == '?')
					break;
			}
			var_name = ft_substr(input, i, end - i);
			if (var_name == NULL)
				return (ft_free(input));
			if (ft_strncmp(var_name, "?", 1) == 0)
			{
				ft_free(var_name);
				var_value = ft_itoa(g_exit_code);
				if (var_value == NULL)
					return (ft_free(input));
			}
			else
			{
				var_value = get_var_value(env_vars, var_name);
				ft_free(var_name);
				if (var_value)
				{
					var_value = ft_strdup(var_value);
					if (var_value == NULL)
						return (ft_free(input));
				}
			}
			input = ft_insert_str(input, var_value, i, end);
			i += ft_strlen(var_value) - 1;
			ft_free(var_value);
			if (input == NULL)
				return (NULL);
		}
	}
	return (input);
}

char	*expand_tilde(char *input, t_env *env_vars)
{
	uint32_t	i;
	char		*home_var;

	i = 0;
	while (input[i])
	{
		if (ft_isspace(input[i]))
		{
			i++;
			if (is_valid_char(input, i++, '~'))
			{
				if (ft_isspace(input[i]) || (input[i] == '/') || (input[i] == '\0'))
				{
					home_var = get_var_value(env_vars, "HOME");
					input = ft_insert_str(input, home_var, i, i);
					i += ft_strlen(home_var) - 1;
					if (input == NULL)
						return (NULL);
				}
			}
		}
		else
			i++;
	}
	return (input);
}

char	*expand_pid(char *input)
{
	uint32_t	i;
	char		*char_pid;

	i = 0;
	while (input[i])
	{
		if (is_valid_char(input, i++, '$'))
		{
			if (is_valid_char(input, i, '$'))
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
