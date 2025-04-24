/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_related.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:12:08 by asoudani          #+#    #+#             */
/*   Updated: 2025/04/24 17:31:58 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	arguments_error(void)
{
	printfd(2, RED "\nPhilo expects the following:\n" RESET);
	printfd(2, "1. The number of philosophers\n");
	printfd(2, "2. The time a philosopher must eat before or they die\n");
	printfd(2, "3. The time each philosopher spends while eating\n");
	printfd(2, "4. The time each philosopher spends sleeping\n");
	printfd(2, "5. The number of meals a philos must eat to stop(opt)\n");
	printfd(2, RED "\nplease make sure that:\n" RESET);
	printfd(2, "1. The number of philosophers is between 1 and 200\n");
	printfd(2, "2. The time to die, eat and sleep are greater than 60ms\n");
	printfd(2, "4. The arguments are positive integers\n");
	printfd(2, "5. The arguments are not empty\n\n");
	return (ERROR);
}

int	argument_checkers(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (ft_atol(av[1]) < 0)
			return (arguments_error(), ERROR);
		if (non_num_found(av[i]) || ft_atol(av[i]) == INT_MIN)
		{
			if (ft_atol(av[i]) == INT_MIN)
				return (printfd(2, RED "Int Overflow Detected.\n" RESET),
					ERROR);
			return (arguments_error(), ERROR);
		}
		if ((i != 5 && i != 1 && ft_atol(av[i]) == 0))
			return (arguments_error(), ERROR);
		if (av[5] && ft_atol(av[i]) == 0)
			exit(0);
		i++;
	}
	return (SUCCESS);
}

int	av_arguments_init(t_data *data, char **av)
{
	data->should_start = false;
	data->ender = false;
	data->philo_died = false;
	data->last_mealtime = 0;
	data->start_time = ms_curr_time();
	data->number_of_philos = ft_atol(av[1]);
	data->ids = malloc(sizeof(int) * data->number_of_philos);
	data->time_to_die = ft_atol(av[2]);
	data->time_to_eat = ft_atol(av[3]);
	data->time_to_sleep = ft_atol(av[4]);
	if (av[5])
		data->must_eat_number = ft_atol(av[5]);
	else
		data->must_eat_number = -1;
	return (SUCCESS);
}
