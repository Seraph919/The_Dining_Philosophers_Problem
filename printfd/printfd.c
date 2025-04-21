/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printfd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:14:53 by asoudani          #+#    #+#             */
/*   Updated: 2025/04/21 17:37:09 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printfd.h"

static int	while_loop(t_args *args)
{
	while (*(args->form))
	{
		if (*(args->form) == '%' && check_char(*((args->form) + 1)) == 1)
		{
			(args->form) = formats((args->form), args->args, &args->count,
					args);
			if (args->err == -1)
				return (-1);
			(args->form)++;
		}
		else if (*(args->form) != '%')
		{
			if (putcharr_fd(*(args->form), args->fd, &args->count) == -1)
			{
				va_end(args->args);
				return (-1);
			}
		}
		(args->form)++;
	}
	return (args->count);
}

void	args_init(t_args *args, int fd, const char *from)
{
	args->form = from;
	args->count = 0;
	args->err = 0;
	args->fd = fd;
}

int	printfd(int fd, const char *form, ...)
{
	t_args	args;

	args_init(&args, fd, form);
	if (!form)
		return (0);
	va_start(args.args, form);
	args.count = 0;
	args.count = while_loop(&args);
	if (args.err == -1)
		return (-1);
	va_end(args.args);
	return (args.count);
}
