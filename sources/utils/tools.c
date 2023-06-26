/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tools.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/20 19:09:49 by fra           #+#    #+#                 */
/*   Updated: 2023/06/26 16:38:43 by yzaim         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	move_chars(char *dest, char *src)
{
	uint32_t	i;
	uint32_t	j;

	i = 0;
	j = 0;
	while (src[j])
	{
		if (! is_valid_quote(src, j))
			dest[i++] = src[j];
		j++;
	}
}

char	*remove_quotes(char *to_clear, bool free_string)
{
	char		*cleaned_str;
	uint32_t	len;
	uint32_t	i;

	len = ft_strlen(to_clear);
	i = 0;
	while (to_clear[i])
	{
		if (is_valid_quote(to_clear, i))
			len--;
		i++;
	}
	if (i == len)
		cleaned_str = ft_strdup(to_clear);
	else
	{
		cleaned_str = ft_calloc(len + 1, sizeof(char));
		if (cleaned_str)
			move_chars(cleaned_str, to_clear);
	}
	if (free_string == true)
		ft_free(to_clear);
	return (cleaned_str);
}

bool	is_quote(char to_check)
{
	return ((to_check == '\'') || (to_check == '\"'));
}

bool	is_arrow(char to_check)
{
	return ((to_check == '<') || (to_check == '>'));
}

char	*create_file_name(const char *fix_part, int32_t cnt)
{
	char			*file_name;
	char			*char_cnt;

	char_cnt = ft_itoa(cnt);
	if (char_cnt == NULL)
		return (NULL);
	file_name = ft_strjoin((char *) fix_part, char_cnt, "_", false);
	ft_free(char_cnt);
	return (file_name);
}
