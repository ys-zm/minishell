/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: anonymous <anonymous@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/03 23:49:07 by anonymous     #+#    #+#                 */
/*   Updated: 2023/03/20 03:51:55 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H 
# include "libft.h"

// printf in stdout the string str and eventually vargs
// @param str	--> const string to print
// @param varag	--> prints variable arguments (see print_ph())
//
// @return int	--> total numbers of chars written
int		ft_printf(const char *str, ...);

// called when a placeholder is found, the functions finds the type of ph
// and prints it, using the flag (' ' '+' '#') if present
// @param ptr	--> variable pointer thatrepresents the entity to print
// @param ph	--> the associated placeholder
// @param flag	--> flag
//
// @return int	--> total numbers of chars written
size_t	print_ph(va_list *ptr, char ph, char flag);

// checks if the char to_check is a placeholder, i.e. belongs to the set
// ('d' 'i' 'u' 'x' 'X' 'p' 's' 'c' '%')
// @param to_check	--> character to check
//
// return int	--> true/false
int		check_char(char to_check);

// loops through the string checking if every ph char ('%') is followed by the
// correct letter or simbol for flag or type
// @param str	--> string to check
//
// return int	--> true/false
int		check_str(const char *str);

// prints in the stdout the int to_print, prints also the + sign if 
// flag == '+'
// @param to_print  --> int to print
// @param flag		--> il flag == '+' adds the positive sign to the number,
//						does nothing otherwise
// @return size_t	--> total numbers of chars written
size_t	print_int(int to_print, char flag);

// prints in the stdout the unsigned int to_print
// @param to_print  --> unsigned int to print
//
// @return size_t	--> total numbers of chars written
size_t	print_uint(unsigned int to_print);

// prints in the stdout the hexadecimal number to_print, if capital == 1 uses
// upper-case letters, if flag == 1 prints the starting 0x/0X chars
// @param to_print  --> number (hexadeciaml) to print
// @param capital	--> uses capital of small letters of the string (and flag 
//                      also complies)
//
// @return size_t	--> total numbers of chars written
size_t	print_hex(unsigned int to_print, int capital, char flag);

// prints in the stdout string
// @param to_print  --> string to print
//
// @return size_t	--> total numbers of chars written
// NB: if str == NULL it prints "(null)"
size_t	print_str(char *to_print);

// prints in the stdout a pointer, adding 0x at the start
// @param to_print  --> string to print
//
// @return size_t	--> total numbers of chars written
size_t	print_ptr(size_t to_print);

#endif
