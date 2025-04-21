/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_memory.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:36:26 by asoudani          #+#    #+#             */
/*   Updated: 2025/04/07 13:32:55 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printfd.h"

static int	splitting_f(char *adress, char *hex, size_t n, int *nb)
{
	int	i;

	i = 1;
	while (n > 0)
	{
		adress[i] = hex[n % 16];
		n /= 16;
		i++;
	}
	while (--i)
		if (putcharr_fd(adress[i], 1, nb) == -1)
			return (-1);
	return (1);
}

static void	free_all(char *adress)
{
	free(adress);
}

int	p_memory(void *ad, int fd, int *nb)
{
	size_t	n;
	char	*hex;
	char	*adress;

	adress = malloc(18 * sizeof(char));
	if (!adress)
		return (-1);
	hex = "0123456789abcdef";
	n = (size_t)ad;
	if (putstrr_fd("0x", fd, nb) == -1)
		return (free_all(adress), -1);
	if (n == 0)
	{
		if (putcharr_fd('0', fd, nb) == -1)
			return (free_all(adress), -1);
	}
	else
	{
		if (splitting_f(adress, hex, n, nb) == -1)
			return (free_all(adress), -1);
	}
	free(adress);
	return (1);
}
