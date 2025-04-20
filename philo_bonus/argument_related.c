/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_related.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:12:08 by asoudani          #+#    #+#             */
/*   Updated: 2025/04/20 20:01:21 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	arguments_error(void)
{
	printf("the program expects the following:\n./philo ");
	printf("%s<%snumber_of_philosophers%s>%s ", BLUE, GREEN, BLUE, RESET);
	printf("%s<%stime_to_die%s> %s ", BLUE, GREEN, BLUE, RESET);
	printf("%s<%stime_to_eat%s> %s ", BLUE, GREEN, BLUE, RESET);
	printf("%s<%stime_to_sleep%s> %s ", BLUE, GREEN, BLUE, RESET);
	printf("%s<%s(opt):[Number of Meals]%s> %s\n", BLUE, GREEN, BLUE, RESET);
	return (ERROR);
}

int	argument_checkers(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (ft_atol(av[1]) < 1 || ft_atol(av[1]) == 0)
			return (printf(RED "2 or more Philos are required.\n" RESET),
				ERROR);
		if (ft_atol(av[1]) > 200)
			return (printf(RED "Philos're more than 200.\n" RESET), ERROR);
		if (non_num_found(av[i]))
			return (arguments_error(), ERROR);
		if ((i != 5 && ft_atol(av[i]) == 0))
			return (printf(RED "Please provide a valid input.\n" RESET), ERROR);
		if (i != 1 && i != 5 && ft_atol(av[i]) < 60)
			return (printf(RED "Times should be above 60ms.\n" RESET), ERROR);
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
