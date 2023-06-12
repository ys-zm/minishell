/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: anonymous <anonymous@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/04 00:21:51 by anonymous     #+#    #+#                 */
/*   Updated: 2023/03/20 03:54:46 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	check_char(char to_check)
{
	char	*str_check;

	str_check = "csd%iupxX";
	while (*str_check)
	{
		if (to_check == *str_check++)
			return (1);
	}
	return (0);
}

int	check_str(const char *str)
{
	while (*str)
	{
		if (*str++ == '%')
		{
			if (*str == '#' || *str == ' ' || *str == '+')
				str++;
			if (! check_char(*str))
				return (0);
			if (*str == '%')
				str++;
		}
	}
	return (1);
}

size_t	print_ph(va_list *ptr, char ph, char flag)
{
	size_t	chars_written;

	chars_written = 0;
	if (ph == 'c')
		chars_written += ft_putchar_fd(va_arg(*ptr, int), 1);
	else if (ph == '%')
		chars_written += ft_putchar_fd('%', 1);
	else if (ph == 's')
		chars_written += print_str(va_arg(*ptr, char *));
	else if (ph == 'p')
		chars_written += print_ptr(va_arg(*ptr, size_t));
	else if (ph == 'd' || ph == 'i')
		chars_written += print_int(va_arg(*ptr, int), flag);
	else if (ph == 'u')
		chars_written += print_uint(va_arg(*ptr, unsigned int));
	else if (ph == 'x')
		chars_written += print_hex(va_arg(*ptr, unsigned int), 0, flag);
	else if (ph == 'X')
		chars_written += print_hex(va_arg(*ptr, unsigned int), 1, flag);
	return (chars_written);
}

int	ft_printf(const char *str, ...)
{
	va_list	ptr;
	size_t	cnt;
	char	flag;

	cnt = 0;
	if (! check_str(str))
		return (-1);
	va_start(ptr, str);
	while (*str)
	{
		if (*str++ == '%')
		{
			if (*str == '#' || *str == '+' || *str == ' ')
				flag = *str++;
			else
				flag = 0;
			cnt += print_ph(&ptr, *str++, flag);
		}
		else
			cnt += ft_putchar_fd(*(str - 1), 1);
	}
	va_end(ptr);
	return (cnt);
}
