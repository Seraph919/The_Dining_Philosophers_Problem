/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:28:13 by asoudani          #+#    #+#             */
/*   Updated: 2025/04/25 18:55:01 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	simulation(t_data *data)
{
	int	i;

	i = -1;
	data->start_time = ms_curr_time();
	while (++i < data->philo_nbrs)
	{
		if (pthread_create(&data->philo_ths[i], NULL, &routine,
				&data->philos[i]))
			return (ERROR);
	}
	if (pthread_create(&data->monitor_th, NULL, &monitor, data))
		return (ERROR);
	if (pthread_join(data->monitor_th, NULL) != SUCCESS)
		return (ERROR);
	i = -1;
	while (++i < data->philo_nbrs)
	{
		if (pthread_join(data->philo_ths[i], NULL) != SUCCESS)
			return (ERROR);
	}
	return (SUCCESS);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 5 || ac > 6)
		return (arguments_error(), ERROR);
	if (argument_checkers(av) != SUCCESS)
		return (ERROR);
	if (ft_atol(av[1]) == 0 || (av[5] && ft_atol(av[5]) == 0))
		return (SUCCESS);
	if (initialization(&data, av) != SUCCESS)
		return (return_error("Initialization failed\n"));
	if (simulation(&data) != SUCCESS)
		return (return_error("Threads failed\n"));
	fireforce(&data);
	return (SUCCESS);
}
