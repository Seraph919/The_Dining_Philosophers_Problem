/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:14:04 by asoudani          #+#    #+#             */
/*   Updated: 2025/04/24 18:02:49 by asoudani         ###   ########.fr       */
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
		pthread_mutex_init(&data->philos[i].meal_mutex, NULL);
		pthread_mutex_init(&data->philos[i].full_mutex, NULL);
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

int	semaphore_init(t_data *data)
{
	sem_unlink("/philo_forks");
	sem_unlink("/meals");
	sem_unlink("/print_bool");
	sem_unlink("/philo_bool_lock");
	sem_unlink("/stop");
	sem_unlink("/philo_print_lock");
	sem_unlink("/full_sem");
	data->forks = sem_open("/philo_forks", O_CREAT | O_EXCL, 0644,
			data->number_of_philos);
	data->meals = sem_open("/meals", O_CREAT | O_EXCL, 0644, 0);
	data->full_sem = sem_open("/full_sem", O_CREAT | O_EXCL, 0644, 1);
	data->print_bool = sem_open("/print_bool", O_CREAT | O_EXCL, 0644, 0);
	data->bool_lock = sem_open("/philo_bool_lock", O_CREAT | O_EXCL, 0644, 1);
	data->stop = sem_open("/stop", O_CREAT | O_EXCL, 0644, 0);
	data->print_lock = sem_open("/philo_print_lock", O_CREAT | O_EXCL, 0644, 1);
	if (data->forks == SEM_FAILED || data->bool_lock == SEM_FAILED
		|| data->stop == SEM_FAILED || data->print_bool == SEM_FAILED
		|| data->print_lock == SEM_FAILED || data->meals == SEM_FAILED
		|| data->full_sem == SEM_FAILED)
		return (ERROR);
	return (SUCCESS);
}

int	data_init(t_data *data, char **av)
{
	if (av_arguments_init(data, av))
		return (ERROR);
	if (semaphore_init(data))
		return (free(data->ids),
			exit_message("Semaphore creation error", ERROR), 1);
	data->print_bool->__align = 1;
	data->first_death = true;
	data->meals->__align = data->number_of_philos;
	if (philo_init(data) == ERROR)
		return (ERROR);
	if (pthread_mutex_init(&data->philo_died_mut, NULL) != 0)
		return (fireforce(data), ERROR);
	return (SUCCESS);
}
