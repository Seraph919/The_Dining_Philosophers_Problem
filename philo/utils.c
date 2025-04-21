/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:40:16 by asoudani          #+#    #+#             */
/*   Updated: 2025/04/21 17:40:48 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	ft_atol(const char *str)
{
	size_t	i;
	size_t	number;

	i = 0;
	number = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\v' || str[i] == '\n'
		|| str[i] == '\r' || str[i] == '\f')
		i++;
	if (str[i] == '+')
		i++;
	while ((str[i] >= '0' && str[i] <= '9'))
	{
		number = number * 10 + (str[i++] - '0');
		if (number >= 2147483647)
			return (-2147483648);
	}
	return (number);
}

bool	non_numeric_found(char *s)
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

void	usleepp(size_t sleep_time)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < sleep_time)
		usleep(500);
}

size_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return ((tv.tv_sec * (size_t)1000) + (tv.tv_usec / 1000));
}

int	return_error(char *msg)
{
	printfd(2, "%s\n", msg);
	return (ERROR);
}
