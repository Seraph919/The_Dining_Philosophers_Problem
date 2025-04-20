/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 02:10:11 by asoudani          #+#    #+#             */
/*   Updated: 2025/04/20 15:23:50 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int main(int ac, char **av)
{
	t_data data;
	// write errors in stderr
	if (ac > 6 || ac < 5)
		return (arguments_error());
	if (argument_checkers(av) || data_init(&data, av) == ERROR)
		return (ERROR);
	if (dinningSim(&data) == ERROR)
		return (ERROR);
	fireforce(&data);
	return (SUCCESS);
}