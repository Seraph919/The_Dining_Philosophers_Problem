/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:09:42 by asoudani          #+#    #+#             */
/*   Updated: 2025/04/20 20:03:52 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/*
	rotine function is used to run the main loop of the philosopher
	it creates a thread for the monitor function and then it runs the eating,
	sleeping and thinking functions in a loop.
	it also checks if the philosopher is dead or not by using a mutex lock
	to protect the access to the dead flag to avoid deadlock.
*/

void	death_occurred(t_philo *philo)
{
	pthread_mutex_unlock(&philo->last_meal_up);
	pthread_mutex_lock(&philo->dead_lock);
	philo->dead = true;
	pthread_mutex_unlock(&philo->dead_lock);
	print_message(philo, DIED);
	sem_post(philo->data->quiter);
}

void	rotine(t_philo *philo)
{
	if (philo->id % 2 == 0)
		mssleep(philo->data->time_to_eat - 10);
	philo->last_meal_t = ms_curr_time();
	while (1)
	{
		pthread_mutex_lock(&philo->last_meal_up);
		if (philo->data->time_to_die <= ms_curr_time() - philo->last_meal_t)
		{
			death_occurred(philo);
			break ;
		}
		pthread_mutex_unlock(&philo->last_meal_up);
		pthread_mutex_lock(&philo->dead_lock);
		if (philo->dead == true)
		{
			pthread_mutex_unlock(&philo->dead_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->dead_lock);
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
}

void	handle_1_philo(t_data *data, int id)
{
	print_message(&data->philos[id], FORK);
	mssleep(data->time_to_die);
	pthread_mutex_lock(&data->philos[id].dead_lock);
	data->philos[id].dead = true;
	pthread_mutex_unlock(&data->philos[id].dead_lock);
	print_message(&data->philos[id], DIED);
	sem_post(data->quiter);
	fireforce(data);
	exit(SUCCESS);
}

void	dinning(t_data *data, int id)
{
	if (data->number_of_philos == 1)
		handle_1_philo(data, id);
	rotine(&data->philos[id]);
	fireforce(data);
}

int	simulation(t_data *data)
{
	size_t	i;

	i = 0;
	sem_wait(data->quiter);
	while (i < data->number_of_philos)
	{
		data->ids[i] = fork();
		if (data->ids[i] == 0)
		{
			dinning(data, i);
			exit(SUCCESS);
		}
		else if (data->ids[i] < 0)
		{
			return (ERROR);
		}
		i++;
	}
	if (data->must_eat_number == -1 || risky(data))
		waitfor_death(data, i);
	else
		waitformeals(data, i);
	return (SUCCESS);
}
