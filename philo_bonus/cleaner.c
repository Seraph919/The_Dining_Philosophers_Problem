/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:58:32 by asoudani          #+#    #+#             */
/*   Updated: 2025/04/24 17:47:56 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	post_and_end(t_philo *philo)
{
	pthread_mutex_unlock(&philo->meal_mutex);
	pthread_mutex_lock(&philo->full_mutex);
	philo->full = true;
	pthread_mutex_unlock(&philo->full_mutex);
	sem_wait(philo->data->full_sem);
	philo->data->meals->__align -= 1;
	sem_post(philo->data->full_sem);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

void	close_sems(t_data *data)
{
	sem_close(data->forks);
	sem_close(data->bool_lock);
	sem_close(data->meals);
	sem_close(data->print_lock);
	sem_close(data->stop);
	sem_close(data->print_bool);
	sem_close(data->full_sem);
	sem_unlink("/philo_forks");
	sem_unlink("/meals");
	sem_unlink("/print_bool");
	sem_unlink("/philo_bool_lock");
	sem_unlink("/stop");
	sem_unlink("/philo_print_lock");
	sem_unlink("/full_sem");
}

void	fireforce(t_data *data)
{
	size_t	i;

	i = -1;
	while (++i < data->number_of_philos)
	{
		pthread_mutex_destroy(&data->philos[i].meal_mutex);
		pthread_mutex_destroy(&data->philos[i].dead_lock);
		pthread_mutex_destroy(&data->philos[i].last_meal_up);
		pthread_mutex_destroy(&data->philos[i].full_mutex);
	}
	pthread_mutex_destroy(&data->philo_died_mut);
	close_sems(data);
	if (data->philos)
		free(data->philos);
	if (data->ids)
		free(data->ids);
	exit(SUCCESS);
}

void	waitformeals(t_data *data, int i)
{
	while (i > 0)
	{
		waitpid(data->ids[i - 1], NULL, 0);
		i--;
	}
}

void	waitfor_death(t_data *data, int i)
{
	while (data->stop->__align != 1 || (data->meals->__align > 0
			|| data->must_eat_number != -1))
	{
		if (data->meals->__align == 0 || data->stop->__align == 1)
			break ;
	}
	usleep(200);
	while (i > 0)
	{
		kill(data->ids[i - 1], SIGKILL);
		i--;
	}
}
