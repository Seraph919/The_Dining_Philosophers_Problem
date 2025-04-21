/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putstrr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 18:30:35 by asoudani          #+#    #+#             */
/*   Updated: 2025/04/07 13:32:37 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printfd.h"

int	putstrr_fd(char *s, int fd, int *n)
{
	if (!s)
	{
		if (putstrr_fd("(null)", fd, n) == -1)
			return (-1);
	}
	else
	{
		while (*s)
		{
			if (putcharr_fd(*s, fd, n) == -1)
				return (-1);
			s++;
		}
	}
	return (1);
}
