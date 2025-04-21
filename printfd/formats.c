/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formats.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:23:20 by asoudani          #+#    #+#             */
/*   Updated: 2025/04/07 13:33:49 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printfd.h"

const char	*formats(const char *form, va_list argss, int *n, t_args *args)
{
	if (*(form + 1) == 'd' || *(form + 1) == 'i')
		args->err = putnbrr_fd_fd(va_arg(argss, int), args->fd, n);
	else if (*(form + 1) == 's')
		args->err = putstrr_fd(va_arg(argss, char *), args->fd, n);
	else if (*(form + 1) == 'p')
		args->err = p_memory(va_arg(argss, void *), args->fd, n);
	else if (*(form + 1) == 'x')
		args->err = p_hexa(va_arg(argss, int), args->fd, n);
	else if (*(form + 1) == 'u')
		args->err = unsigned_int(va_arg(argss, unsigned int), args->fd, n);
	else if (*(form + 1) == 'X')
		args->err = upper_hexa(va_arg(argss, int), args->fd, n);
	else if (*(form + 1) == '%')
		args->err = putcharr_fd('%', args->fd, n);
	else if (*(form + 1) == 'c')
		args->err = putcharr_fd(va_arg(argss, int), args->fd, n);
	else if (*(form + 1) == '\0')
		return (form);
	return (form);
}
