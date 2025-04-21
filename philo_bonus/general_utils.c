/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:09:12 by asoudani          #+#    #+#             */
/*   Updated: 2025/04/21 17:34:05 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*
	struct timeval is used to get the current time in seconds and microseconds
	we get the current time in seconds and microseconds using gettimeofday
	then we convert the seconds to miliseconds by multiplying it by 1000
	and we convert the microseconds to miliseconds by dividing it by 1000
	then we add the two values together to get the current time in miliseconds
*/
size_t	ms_curr_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((size_t)tv.tv_sec * 1000 + (size_t)tv.tv_usec / 1000);
}

/*
	mssleep is used to sleep for a given number of milliseconds
	we get the current time in milliseconds and we sleep for 200 microseconds
	until the difference between the current time and the start
	time is greater than
	the given number of milliseconds
*/

void	mssleep(size_t milliseconds)
{
	size_t	start;

	start = ms_curr_time();
	while ((ms_curr_time() - start) < (milliseconds))
		usleep(200);
	return ;
}

bool	non_num_found(char *s)
{
	if (!s)
		return (true);
	if (*s == '+')
		s++;
	while (*s)
	{
		if (*s <= '9' && *s >= '0')
			s++;
		else
			return (true);
	}
	return (false);
}

void	exit_message(char *s, int status)
{
	if (!s)
		exit(status);
	printfd(2, "%s\n", s);
	exit(status);
}

unsigned long	ft_atol(const char *str)
{
	unsigned long	i;
	unsigned long	number;

	i = 0;
	number = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\v' || str[i] == '\n'
		|| str[i] == '\r' || str[i] == '\f')
		i++;
	if (str[i] == '+')
		i++;
	while ((str[i] >= '0' && str[i] <= '9'))
		number = number * 10 + (str[i++] - '0');
	return (number);
}
