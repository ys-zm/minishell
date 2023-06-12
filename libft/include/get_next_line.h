/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/23 05:52:23 by fra           #+#    #+#                 */
/*   Updated: 2023/03/30 01:52:31 by fra           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include "libft.h"
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

// from a given file descriptor read a line (i.e. a sequence of characters 
// beginning at the cursor position and ending before the first occurrence
// of the character \n)
// @param fd    --> file descriptor
//
// return char* --> the line read, NULL if:
//                      1) allocation fails;
//                      2) file descriptor is invalid (file not esixistent or 
//                          permission issues) also prints it in stderr
//                      3) reached EOF
// NB: the position of the cursor is not resetted when the fd is closed but EOF
//      is not reached
char	*get_next_line(int fd);

// finds the position of the next new line char
// @param str   --> string to inspect
//
// @return int  --> position of \n, -1 if non present
int		find_nl_pos(char *str);

// returns the length of the substring of the buffer from the start until the
// next new line char
// @param buffer    --> string to inspect
//
// @return int      --> length of substring
// NB: len(buffer) if no new_line is present
int		length_new_str(char *buffer);

// shifts the characters of str until the character after the first new line
// char found
// @param str   --> string to inspect
//
// @preturn int --> the number of characters erased
int		shift_chars(char *str);

// appends the characters of buffer from 0 to the first new_line char found
// (or until the end of buffer) to the ones in old creating a new string
// @param old       --> string to be appended
// @param buffer    --> the substring until new_line is extracted from buffer
//
// return char*     --> the new string appended
// NB: the function does MALLOC
char	*append_str(char *old, char *buffer);

#endif