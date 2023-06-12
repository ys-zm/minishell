/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_usleep.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: faru <faru@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/02 17:16:22 by faru          #+#    #+#                 */
/*   Updated: 2023/05/02 17:20:16 by faru          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int32_t	delta_time(struct timeval t1, struct timeval t2)
{
	struct timeval	delta;
	int32_t			timestamp;

	while ((t2.tv_usec < t1.tv_usec) && (t2.tv_sec > t1.tv_sec))
	{
		t2.tv_usec += 1000000;
		t2.tv_sec -= 1;
	}
	delta.tv_sec = t2.tv_sec - t1.tv_sec;
	delta.tv_usec = t2.tv_usec - t1.tv_usec;
	timestamp = delta.tv_sec * 1000000 + delta.tv_usec;
	return (timestamp / 1000);
}

void	ft_msleep(uint32_t milli_secs)
{
	struct timeval	start;
	struct timeval	current;

	gettimeofday(&start, NULL);
	gettimeofday(&current, NULL);
	while (delta_time(start, current) < (int32_t) milli_secs)
	{
		usleep(50);
		gettimeofday(&current, NULL);
	}
}
