/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_xatof.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/05 04:22:45 by fra           #+#    #+#                 */
/*   Updated: 2023/03/19 04:12:48 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	find_hexa_char(char c_to_cast)
{
	if (c_to_cast > 'A' && c_to_cast < 'Z')
		return (ft_find_index("0123456789ABCDEF", c_to_cast));
	else
		return (ft_find_index("0123456789abcdef", c_to_cast));
}

static int	shift_until_valid_digit(char **str_n)
{
	int	sign;

	sign = 1;
	while (ft_isspace(**str_n))
		(*str_n)++;
	if (**str_n == '-' || **str_n == '+')
	{
		if (**str_n == '-')
			sign = -1;
		(*str_n)++;
	}
	if (! ft_memcmp(str_n, "0x", 2))
	{
		(*str_n)++;
		(*str_n)++;
	}
	return (sign);
}

float	ft_xatof(char *str_n)
{
	float	nbr;
	int		sign;
	int		comma_pos;
	int		i;

	nbr = 0;
	comma_pos = -1;
	sign = shift_until_valid_digit(&str_n);
	i = 0;
	while (ft_ishexadigit(str_n[i]))
	{
		if (comma_pos != -1 && (str_n[i] == ',' || str_n[i] == '.'))
			comma_pos = i++;
		if (! ft_memcmp(str_n + i, "0x", 2))
		{
			i += 2;
			comma_pos += 2;
		}
		nbr = (nbr * 16) + find_hexa_char(str_n[i++]);
	}
	if (comma_pos != -1)
		nbr *= ft_pow(16, comma_pos - i + 1);
	return (nbr * sign);
}
