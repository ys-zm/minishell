#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*(unsigned char *)s1 - *(unsigned char *)s2);
		s1++;
		s2++;
	}
	if (!*s1 || !*s2)
		return (*(unsigned char *)s1 - *(unsigned char *)s2);
	return (0);
}

char	*ft_trip_join(char *str1, char *str2, char *str3)
{
	char	*first_two;
	char	*plus_three;

	first_two = ft_strjoin(str1, str2, "", false);
	plus_three = ft_strjoin(first_two, str3, "", false);
	free(first_two);
	return (plus_three);
}

size_t	count_args(char **args)
{
	size_t	count;

	count = 0;
	while (args[count])
		count++;
	return(count);
}
