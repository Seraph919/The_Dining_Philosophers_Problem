/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putnbrr_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 17:38:30 by asoudani          #+#    #+#             */
/*   Updated: 2025/04/21 17:38:30 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printfd.h"

static int	double_while(long n, int *nbr)
{
	long	i;

	i = 1;
	while (i * 10 <= n)
	{
		i *= 10;
	}
	while (i > 0)
	{
		if (putcharr_fd((n / i) + '0', 1, nbr) == -1)
			return (-1);
		n %= i;
		i /= 10;
	}
	return (1);
}

int	putnbrr_fd_fd(int nb, int fd, int *nbr)
{
	long	n;

	n = nb;
	if (n < 0)
	{
		if (putcharr_fd('-', fd, nbr) == -1)
			return (-1);
		n *= -1;
	}
	if (n == 0)
	{
		if (putcharr_fd('0', fd, nbr) == -1)
			return (-1);
		return (1);
	}
	if (double_while(n, nbr) == -1)
		return (-1);
	return (1);
}
