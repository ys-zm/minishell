/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fra <fra@student.42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/09 15:17:04 by anonymous     #+#    #+#                 */
/*   Updated: 2023/05/31 18:21:09 by faru          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stddef.h>		// NULL, size_t type
# include <stdlib.h>    	// malloc(), free()
# include <unistd.h>    	// write(), read(), open(), close(), ...
# include <fcntl.h>			// macro to open files (O_CREAT, O_RDONLY ..)
# include <stdint.h>		// cross-compiler types
# include <limits.h>		// limits of types (INT_MAX, LONG_MAX, ...)
# include <stdarg.h>		// variable number of arguments
# include <sys/time.h>		// gettimeofday(), timeval_t
# include <stdint.h>		// cross-compiler types
# include <stdbool.h>		// boolean types
# include "get_next_line.h"
# include "ft_printf.h"

// implementation of a linked list
// @param content	--> void pointer to content of the node
// @param next		--> pointer to next element of linked list
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

// checks if the character is a letter (a-z or A-Z) or a digit (0-9)
// @param character	--> char to check
//
// @return	int		--> true/false
int		ft_isalnum(int character);

// checks if the character is a letter (a-z or A-Z)
// @param character	--> char to check
//
// @return	int		--> true/false
int		ft_isalpha(int character);

// checks if the character is ASCII
// @param character	--> char to check
//
// @return	int		--> true/false
int		ft_isascii(int character);

// checks if the character is a digit (0-9)
// @param character	--> char to check
//
// @return	int		--> true/false
int		ft_isdigit(int character);

// checks if the character is a hexadecimal digit (0-9, a-f, A-F)
// @param character	--> char to check
//
// @return	int		--> true/false
int		ft_ishexadigit(int character);

// checks if the character is printable (i.e. visible in stdout)
// @param character	--> char to check
//
// @return	int		--> true/false
int		ft_isprint(int character);

// checks if the character is a type of space (' ', \t, \n, ...)
// @param character	--> char to check
//
// @return	int		--> true/false
int		ft_isspace(char character);

// convert the character in upper-case (a->A)
// @param character	--> char to upper
//
// @return int		--> the upper char of the letter, otherwise the given char
int		ft_toupper(int a);

// convert the character in lower-case (A->a)
// @param character	--> char to lower
//
// @return int		--> the lower char of the letter, otherwise the given char
int		ft_tolower(int a);

// checks if the string represents a decimal or hexadecimal number
// @param number  	--> string/char ptr to check
//
// @return	int 	--> true/false
int		ft_is_number(char *number);

// checks if the string represents a decimal or hexadecimal integer
// @param number  	--> string/char ptr to check
//
// @return	int 	--> true/false
int		ft_is_int(char *number);

// checks if the string represents a decimal or hexadecimal long
// @param number  	--> string/char ptr to check
//
// @return	int 	--> true/false
int		ft_is_long(char *number);

// prints the given character to the file given descriptor
// @param character		--> char to print
// @param fd			--> int representing the fd
//
// @return size_t		--> the amount of chars successfully written
size_t	ft_putchar_fd(char character, int fd);

// prints the given string to the file given descriptor
// @param string		--> string to print
// @param fd			--> int representing the fd
//
// @return size_t		--> the amount of chars successfully written
size_t	ft_putstr_fd(char *string, int fd);

// prints the given string followed by a new line to the file given descriptor
// @param string		--> string to print
// @param fd			--> int representing the fd
//
// @return size_t		--> the amount of chars successfully written
size_t	ft_putendl_fd(char *string, int fd);

// prints the given string (representing a long) to the file given descriptor
// @param string		--> string to print
// @param fd			--> int representing the fd
//
// @return size_t		--> the amount of chars successfully written
size_t	ft_putnbr_fd(int a, int fd);

// replicates the behaviour of the function usleep() except that the argument
// in meant to be milliseconds, not microseconds (1 millisec = 1000 microsec)
// it has bettere performances than usleep when that function is called
// multiple times
// @param milli_secs	--> amount of milliseconds to sleep
//
// return void
void	ft_msleep(uint32_t milli_secs);

// creates a new element (represented by the value pointed by content)
// @param content	--> value of the new element if the linked list
//
// @return t_list* 	--> the newly created element
// NB: the function does MALLOC
t_list	*ft_lstnew(void *content);

// add the element at the head of the linked list
// @param lst	--> the list to update
// @param new	--> the new element
//
// @return void
void	ft_lstadd_front(t_list **lst, t_list *new);

// add the element at the tail of the linked list
// @param lst	--> the list to update
// @param new	--> the new element
//
// @return void
void	ft_lstadd_back(t_list **lst, t_list *new);

// find the tail of the linked list
// @param lst		--> the list to measure
//
// @return t_list*	--> the last element of the list
t_list	*ft_lstlast(t_list *lst);

// find the length of the linked list
// @param lst	--> the list to measure
//
// @return int	--> the number of the elements
int		ft_lstsize(t_list *lst);

// apply the function del() to the content of the node and then free the list
// @param lst	--> the element to delete
// @param del	--> the function to be applied to lst->content
//
// @return void
void	ft_lstdelone(t_list *lst, void (*del)(void *));

// apply the function ft_lstdelone() to every element of the list
// @param lst	--> the list to clear
// @param del	--> the function to be applied to lst->content
//
// @return void
void	ft_lstclear(t_list **lst, void (*del)(void *));

// apply the function f() to every element of the list
// @param lst	--> the list to clear
// @param f		--> the function to be applied to lst->content
//
// @return void
void	ft_lstiter(t_list *lst, void (*f)(void *));

// create a new list: from the starting list the function f() is applied to the
// content of every element
// @param lst		--> the starting list
// @param f			--> the function to be applied to lst->content
//
// @return t_list*	--> the new list with the f() function applied
// NB: the function does MALLOC
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

// cast ptr from void* into char* and set n_elem elements to null ('\0')
// @param ptr		--> the void ptr to set to zero
// @param n_elem	--> numer of the elements to set to zero
//
// @return void
void	ft_bzero(void *ptr, size_t n_elem);

// allocate space for n_elem elements of size_elem size,
// set every element to null ('\0)
// @param n_elem	--> number of the elements to allocate
// @param size_elem	--> size of every element
//
// @return void*	--> the allocated pointer
// NB: the function does MALLOC
void	*ft_calloc(size_t n_elem, size_t size_elem);

// frees the double pointer to_free and set that address to NULL
// @param **to_free	--> the address of the double pointer to free
// @param n_arr			--> number of the elements of the double pointer
//							if n_arr == -1 the the function assumes that the
//							the double ptr is char** so it keeps iterating
//							untill if finds a NULL ptr, if n_arr > 0 then only
//							n_arr single ptr is going to be freed
//
// @return void*		--> always returns NULL for convenience
void	*ft_free_double(void **to_free, int n_arr);

// wrapper of free(), frees the pointer only if is different from NULL
// @param *ptr_to_free	--> ...
//
// @return void*		--> always returns NULL for convenience
void	*ft_free(void *ptr_to_free);

// checks if the next n characters of str_to_search contain to_find
// @param str_to_search	--> the string to search
// @param to_find		--> the character to find
// @param n				--> number of elements of str_to_search to inspect
//
//	@return	void*		--> represents the pointer that points to the element
//							of str_to_search equals to to_find, NULL otherwise
void	*ft_memchr(const void *str_to_search, int to_find, size_t n);

// compares the first n elements of the two pointers src and dst, checks if they
// are the same
// @param src	--> first pointer
// @param dst	--> second pointer
// @param n		--> number of elements to check
//
// @return int	--> 0 if they're the same, pos/neg number otherwise
int		ft_memcmp(const void *src, const void *dst, size_t n);

// copies up to n elements from src to dst
// @param dst	--> pointer to store the elements
// @param src	--> pointer to copy from the elements
// @param n		--> number of the elements to copy
//
// @return		--> returns the dst pointer
// NB: overlapping is not managed! Use ft_memmove() instead
void	*ft_memcpy(void *dst, const void *src, size_t n);

// works like ft_memcpy() but manges overlapping strings, so it's safer!
// @param dst	--> pointer to store the elements
// @param src	--> pointer to copy from the elements
// @param n		--> number of the elements to copy
//
// @return		--> returns the dst pointer
void	*ft_memmove(void *dst, const void *src, size_t n);

// sets n elements of str to the value to_write
// @param str		--> pointer to set
// @param to_write	--> value to use for every element
// @param n			--> number of the elements to set
//
// @return		--> returns the updated pointer
void	*ft_memset(void *str, int to_write, size_t n);

// prints on the sterr the string text, if end == 1 also terminates the program
// (with exit(EXIT_FAILURE))
// @param test		--> content of the error
// @param end		--> terminate the program if equals to 1
//
// @return void*	--> returns NULL for convenience
void	*ft_raise_error(char *text, int end);

// returns the float representation of the string str (decimal)
// @param str		--> the decimal number to convert into float
//
// @return float	--> the float number that represents the string
// NB: works both with dot of comma, also with - or + signs
float	ft_atof(const char *str);

// returns the integer representation of the string str (decimal)
// @param str	--> the decimal number to convert into integer
//
// @return int	--> the integer number that represents the string
// NB: works both with - or + signs
int		ft_atoi(const char *str);

// returns the long representation of the string str (decimal)
// @param str	--> the decimal number to convert into long
//
// @return long	--> the long number that represents the string
// NB: works both with - or + signs
long	ft_atol(const char *str);

// converts an 8-elements int array of bits (0 or 1 digits) into a 1 byte
// (char) number
// @param bin_char	--> 8-bit array of ints
//
// @return char		--> 1-byte number
char	ft_bin_to_char(int *bin_char);

// converts the 1-byte number in binary digits, updating the array bin_char
// @param number	--> char representing the 1-byte number
// @bin_char		--> 8-bit array of ints to update with the digits of number
//
// return void
void	ft_char_to_bin(char number, int *bin_char);

// converts the given integer into string (decimal representation)
// @param number	--> number to convert
//
// return char*		--> strings that represents (decimal) the number
// NB: the function does MALLOC
char	*ft_itoa(int number);

// converts the given long into string
// @param number	--> number to convert
//
// return char*		--> strings that represents the number
// NB: the function does MALLOC
char	*ft_litoa(long number);

// finds the absolute value of the given number (long)
// @param number	--> number to apply the module operator
//
// @return long		--> absolute value of the number
long	ft_mod(long number);

// finds the absolute value of the given number (float)
// @param number	--> number to apply the module operator
//
// @return long		--> absolute value of the number
float	ft_fmod(float number);

// finds the number of digits of the number written in the given base
// @param number	--> number to inspect
// @param base		--> representation (decimal, binary, octal , ...)
//
// @return u. long	--> absolute value of the number
size_t	ft_nbrlen(long nbr, int base);

// finds the decimal part of the given number (i.e. i - [i])
// @param		--> floating point to inspect
//
// @return		--> decimal part of number
float	ft_part_dec(float number);

// finds the whole part of the given number (i.e. [i] or floor(i))
// @param		--> floating point to inspect
//
// @return		--> integer closest to number
float	ft_part_int(float number);

// rounds number to the closest integer
// @param number	--> floating point to inspect
//
// @return	int		--> rounded number
int		ft_round_to_int(double number);

// applies the power exp to the number base
// @param base		--> number to power
// @param exp		--> number to elevate base
//
// @return float	--> base^exp
float	ft_pow(int base, int exp);

// returns the float representation of the string str (hexadecimal)
// @param str		--> the hexadecimal number to convert into float
//
// @return float	--> the float number that represents the string
// NB: works both with dot of comma, also with - or + signs, ignores characters
//		'0x' both at the start of the string or after the comma/dot (works with
//		0x13.34 and also with 13.0x34)
float	ft_xatof(char *str_n);

// returns the integer representation of the string str (hexadecimal)
// @param str		--> the hexadecimal number to convert into integer
//
// @return integer	--> the integer number that represents the string
// NB: works both with dot of comma, also with - or + signs, ignores characters
//		'0x' both at the start of the string or after the comma/dot (works with
//		0x13.34 and also with 13.0x34)
int		ft_xatoi(char *str);

// converts the given integer into string (hexadecimal representation)
// @param number	--> number to convert
//
// return char*		--> strings that represents (hexadecimal) the number
// NB: the function does MALLOC
char	*ft_xitoa(int a, int capital);

// attaches the character to_add to the string str
// @param str		-->	is the pointer to the string to increase
// @param to_add	--> character to add
//
// @return	char*	--> the new string
// NB: the function assumes that str is a dynamic pointer and at the end it
//		will free it, also the function works if str == NULL
// NB: the function does MALLOC
char	*ft_append_char(char *str, char to_add);

// counts the occurence of the character to_find inside str
// @param str		--> string to inspect
// @param to_find	--> character to find
//
// return int		--> the number of times to_find is in str
int		ft_count_occ(char *str, char to_find);

// finds the index of the first occurence of value in str
// @param str	--> string to inspect
// @param value	--> char to count
//
// @return int	--> index of character value ins str, -1 if non existent
int		ft_find_index(char *str, char value);

// count the number of substrings of str separated by char_split
// @param str			--> string to inspect
// @param char_split	--> separator
//
// @return size_t		--> number of substrings
// NB: ft_n_substr("test|separate||strings|", '|') = 3
size_t	ft_n_substr(char const *str, char char_split);

// splits str into an array of substrings separated by the separator split
// @param str		--> string to split
// @param split		--> separator
// @param trim		--> remove starting and ending spaces
//
// @return	char**	--> se double pointer with the substrings, NULL if str == NULL or mem fail
// NB: the function does MALLOC
char	**ft_split(char const *str, char split, bool trim);

// checks if str_to_search contains to_find
// @param str_to_search	--> the string to search
// @param to_find		--> the character to find
//
//	@return	void*		--> represents the pointer that points to the element
//							of str_to_search equals to to_find, NULL otherwise
char	*ft_strchr(const char *str_to_search, int to_find);

// creates a duplicate of the string str
// @param str		--> string to duplicate
//
// @return char*	--> the duplicate string
// NB: the function does MALLOC
char	*ft_strdup(const char *str);

// applies function f() to every char of string str
// @param str	--> str to modify
// @param f		--> function to apply()
//
// @return void
void	ft_striteri(char *str, void (*f)(unsigned int, char*));

//join the two string s1 and s2
// @param s1			--> first string
// @param ss			--> second string
// @param join_chars	--> join sequence chars
// @param free_stuff	--> if set to true, frees s1 and s2
//
// @return		--> the combined string s = s1 + s2
// NB: the function does MALLOC
char	*ft_strjoin(char *s1, char *s2, const char *join_chars, bool free_stuff);

// concatenate/append at most max_chars - len(src) - 1 characters from the
// string src right after the last non-null char of dst
// @param dst		--> string to concatenate
// @param src		--> string to copy characters 
//
// @return size_t	--> numbers of character effectively written in dst
size_t	ft_strlcat(char *dst, const char *src, size_t max_chars);

// copy at most max_chars - 1 (because null char) from src to dst
// @param dst		--> string to write chars
// @param src		--> string to read chars
//
// @return size_t	--> numbers of character effectively written in dst
size_t	ft_strlcpy(char *dst, const char *src, size_t max_chars);

// length of string
// @param str	--> string to inspect
//
// @return		--> length of str
size_t	ft_strlen(const char *str);

// creates a new string new_str such as: new_str[i] = f(str[i])
// @param str		--> string to inspect
// @param f			--> function to apply
//
// @return char*	--> new string
// NB: the function does MALLOC
char	*ft_strmapi(char const *str, char (*f)(unsigned int, char));

// compares ad most n characters of the stwo string str1 and str2, 0 if they
// are equal
// @param str1	--> first string to inspect
// @param str2	--> second string to inspect
// @param n		--> numbers of elements to inspect
//
// @return	int	--> 0 if the twoo strings match, pos/neg value otherwise
int		ft_strncmp(const char *str1, const char *str2, size_t n);

// checks if string to_find is inside str and if it appears before the
// n_chars - len(to_find) character
// @param str		--> string to inspect
// @pram to_find	--> string to search
// @param n_chars	--> maximum number of characters so that to_find is inside
//						str
//
// @return char*	--> pointer to the first occurrence of to_find in str, NULL
//						otherwise
char	*ft_strnstr(const char *str, char *to_find, size_t n_chars);

// checks if str_to_search contains to_find, starts to seach from the end of 
// str_to_search
// @param str_to_search	--> the string to search
// @param to_find		--> the character to find
//
//	@return	void*		--> represents the pointer that points to the element
//							of str_to_search equals to to_find, NULL otherwise
char	*ft_strrchr(const char *str_to_search, int to_find);

// removes the occurrences of the char set at beginning and ending of str
// @param str	--> string to trim
// @prarm set	--> char to remove
//
// return char*	--> a trimmed new string
// NB: the function does MALLOC
char	*ft_strtrim(char const *str, char const *set);

// creates an fragment from str starting at start and length characters long
// @param str		--> string to extract
// @param start		--> starting index of substring
// @param length	--> legnth of substring
//
// @return char*	--> the substring, NULL if non present or other errors
char	*ft_substr(const char *str, unsigned int start, size_t length);

// removes leading and trailing space characters, gives back the trimmed string
// @param to_trim	--> string to trim
// @param free_str	--> if == true, frees the input string at the end
//
// @return char*	--> trimmed string (NULL for NULL INPUT or mem fail)
// NB: does a malloc
// NB: the function assumes that to_trim is a dynamic pointer and at the end it
//		will free it
char	*ft_trim(char *to_trim);

#endif
