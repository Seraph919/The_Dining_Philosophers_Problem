/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:14:04 by asoudani          #+#    #+#             */
/*   Updated: 2025/04/20 20:01:42 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	philo_init(t_data *data)
{
	size_t	i;

	i = 0;
	data->philos = malloc(sizeof(t_philo) * data->number_of_philos);
	if (!data->philos)
		exit_message("Malloc error", ERROR);
	while (i < data->number_of_philos)
	{
		data->philos[i].data = data;
		data->philos[i].dead = false;
		data->philos[i].id = i + 1;
		data->philos[i].last_meal_t = 0;
		data->philos[i].meal_counter = 0;
		data->philos[i].max_meals = data->must_eat_number;
		pthread_mutex_init(&data->philos[i].m_lock, NULL);
		pthread_mutex_init(&data->philos[i].dead_lock, NULL);
		pthread_mutex_init(&data->philos[i].last_meal_up, NULL);
		i++;
	}
	return (SUCCESS);
}

/*
	when opening a semaphore,
		it's important to unlink the pre-existed one under the same name

*/

int	data_init(t_data *data, char **av)
{
	if (av_arguments_init(data, av))
		return (ERROR);
	sem_unlink("/philo_forks");
	sem_unlink("/philo_quiter");
	sem_unlink("/philo_print_lock");
	data->forks = sem_open("/philo_forks", O_CREAT | O_EXCL, 0644,
			data->number_of_philos);
	data->quiter = sem_open("/philo_quiter", O_CREAT | O_EXCL, 0644, 1);
	data->print_lock = sem_open("/philo_print_lock", O_CREAT | O_EXCL, 0644, 1);
	if (data->forks == SEM_FAILED || data->quiter == SEM_FAILED
		|| data->print_lock == SEM_FAILED)
		exit_message("Semaphore creation error", ERROR);
	if (philo_init(data) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
