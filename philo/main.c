/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:28:13 by asoudani          #+#    #+#             */
/*   Updated: 2025/04/16 18:28:26 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 5 || ac > 6 || argumentCheckers(av)!= SUCCESS)
		return (arguments_error(), ERROR);
	if (initialization(&data, av) != SUCCESS)
		return (return_error("Initialization failed\n"));
	if (thread_creation(&data) != SUCCESS)
		return (return_error("Threads failed\n"));
	if (join_threads(&data) != SUCCESS)
		return (return_error("Joining failed\n"));
	free_data(&data);

	return (SUCCESS);
}
