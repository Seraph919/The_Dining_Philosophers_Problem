/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:58:32 by asoudani          #+#    #+#             */
/*   Updated: 2025/04/20 19:56:45 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void post_and_end(t_philo *philo)
{
	pthread_mutex_unlock(&philo->m_lock);
	pthread_mutex_lock(&philo->dead_lock);
	philo->dead = true;
	pthread_mutex_unlock(&philo->dead_lock);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
	pthread_mutex_lock(&philo->dead_lock);
	if (philo->dead == true && philo->meal_counter != philo->max_meals)
		sem_post(philo->data->quiter);
	pthread_mutex_unlock(&philo->dead_lock);
}

void fireforce(t_data *data)
{
	size_t	i;

	i = -1;
	while (++i < data->number_of_philos)
	{
		pthread_mutex_destroy(&data->philos[i].m_lock);
		pthread_mutex_destroy(&data->philos[i].dead_lock);
		pthread_mutex_destroy(&data->philos[i].last_meal_up);
	}

	sem_close(data->forks);
	sem_close(data->quiter);
	sem_close(data->print_lock);
	sem_close(data->all_full);
	sem_unlink("/philo_forks");
	sem_unlink("/philo_quiter");
	sem_unlink("/philo_print_lock");
	sem_unlink("/philo_all_full");

	if (data->philos)
		free(data->philos);
	if (data->ids)
		free(data->ids);
	exit(SUCCESS);
}

void waitformeals(t_data *data, int i)
{
	while (i > 0)
	{
		waitpid(data->ids[i - 1], NULL, 0);
		i--;
	}
}

void waitforDeath(t_data *data, int i)
{
	sem_wait(data->quiter);
	while (i > 0)
	{
		kill(data->ids[i - 1], SIGKILL);
		i--;
	}
}

bool	risky (t_data *data)
{
	if (data->time_to_die <= data->time_to_eat + data->time_to_sleep)
		return (true);
	return (false);
}
