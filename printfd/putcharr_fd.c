/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putcharr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 18:27:59 by asoudani          #+#    #+#             */
/*   Updated: 2025/04/07 13:28:18 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printfd.h"

int	putcharr_fd(char c, int fd, int *n)
{
	if (write(fd, &c, 1) == -1)
		return (-1);
	*n += 1;
	return (1);
}
