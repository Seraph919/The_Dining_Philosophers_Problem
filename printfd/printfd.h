/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printfd.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 10:15:28 by asoudani          #+#    #+#             */
/*   Updated: 2025/04/21 17:38:12 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTFD_H
# define PRINTFD_H

# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

typedef struct s_args
{
	va_list			args;
	int				count;
	int				err;
	const char		*form;
	int				fd;
}	t_args;

int			printfd(int fd, const char *form, ...);
int			putcharr_fd(char c, int fd, int *n);
int			putstrr_fd(char *s, int fd, int *n);
int			putnbrr_fd_fd(int nb, int fd, int *n);
int			p_memory(void *ad, int fd, int *n);
const char	*formats(const char *form, va_list argss, int *n, t_args *args);
int			p_hexa(unsigned int s, int fd, int *n);
int			upper_hexa(unsigned int s, int fd, int *n);
int			unsigned_int(unsigned int nb, int fd, int *n);
int			check_char(char c);

#endif