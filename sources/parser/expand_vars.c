/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_vars.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/28 01:49:19 by fra           #+#    #+#                 */
/*   Updated: 2023/06/14 17:26:12 by faru          ########   odam.nl         */
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
			while (input[end] && (! ft_isspace(input[end])) && (input[end] != '|') && (! is_quote(input[end])))
				end++;
			var_name = ft_substr(input, i, end - i);
			if (var_name == NULL)
				return (ft_free(input));
			if (ft_strncmp(var_name, "?", 1) == 0)
			{
				var_value = ft_itoa(123);	// g_exit_code
				if (var_value == NULL)
				{
					ft_free(var_name);
					return (ft_free(input));
				}
			}
			else
				var_value = get_var_value(env_vars, var_name);
			ft_free(var_name);
			input = ft_insert_str(input, var_value, i, end);
			if (input == NULL)
				return (NULL);
			i += ft_strlen(var_value) - 1;
		}
	}
	return (input);
}
