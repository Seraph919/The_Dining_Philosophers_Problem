/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_hexa.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:25:15 by asoudani          #+#    #+#             */
/*   Updated: 2025/04/07 13:32:55 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printfd.h"

static void	free_all(char *adress)
{
	free(adress);
}

static void	while_loop(char *reversed, char *hexa, unsigned int s, int *i)
{
	while (s > 0)
	{
		reversed[*i] = hexa[s % 16];
		s /= 16;
		*i += 1;
	}
}

int	p_hexa(unsigned int s, int fd, int *n)
{
	char	*hexa;
	char	*reversed;
	int		i;

	if (s == 0)
	{
		if (putstrr_fd("0", fd, n) == -1)
			return (-1);
	}
	hexa = "0123456789abcdef";
	reversed = malloc(9);
	if (!reversed)
		return (-1);
	i = 0;
	while_loop(reversed, hexa, s, &i);
	reversed[i] = '\0';
	while (i)
		if (putcharr_fd(reversed[--i], fd, n) == -1)
			return (free_all(reversed), -1);
	free(reversed);
	return (1);
}
