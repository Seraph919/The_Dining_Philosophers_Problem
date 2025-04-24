/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 10:09:42 by asoudani          #+#    #+#             */
/*   Updated: 2025/04/24 18:03:20 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// void	death_occurred(t_philo *philo)
// {
// 	pthread_mutex_unlock(&philo->last_meal_up);
// 	pthread_mutex_lock(&philo->dead_lock);
// 	philo->data->stop->__align = 1;
// 	pthread_mutex_unlock(&philo->dead_lock);
// 	print_message(philo, DIED);
// }

bool	checkfordeath(t_philo *philo)
{
	bool	died;

	pthread_mutex_lock(&philo->dead_lock);
	if (philo->dead == true)
		return (pthread_mutex_unlock(&philo->dead_lock), true);
	pthread_mutex_unlock(&philo->dead_lock);
	pthread_mutex_lock(&philo->last_meal_up);
	died = (ms_curr_time() - philo->last_meal_t > philo->data->time_to_die);
	pthread_mutex_unlock(&philo->last_meal_up);
	if (died)
	{
		pthread_mutex_lock(&philo->dead_lock);
		if (philo->dead == true)
			return (pthread_mutex_unlock(&philo->dead_lock), true);
		philo->dead = true;
		if (philo->data->first_death == true)
		{
			print_message(philo, DIED);
			philo->data->stop->__align = 1;
		}
		return (pthread_mutex_unlock(&philo->dead_lock), true);
	}
	return (false);
}

void	rotine(t_philo *philo)
{
	if (philo->id % 2 == 0)
		mssleep(philo->data->time_to_eat - 10, philo, true);
	philo->last_meal_t = ms_curr_time();
	while (1)
	{
		if (checkfordeath(philo))
			break ;
		if (eating(philo))
			break ;
		if (checkfordeath(philo))
			break ;
		if (sleeping(philo))
			break ;
		if (checkfordeath(philo))
			break ;
		if (thinking(philo))
			break ;
	}
}

void	handle_1_philo(t_data *data, int id)
{
	print_message(&data->philos[id], FORK);
	mssleep(data->time_to_die, &data->philos[id], true);
	pthread_mutex_lock(&data->philos[id].dead_lock);
	data->stop->__align = 1;
	pthread_mutex_unlock(&data->philos[id].dead_lock);
	print_message(&data->philos[id], DIED);
	fireforce(data);
	exit(SUCCESS);
}

void	dinning(t_data *data, int id)
{
	if (data->number_of_philos == 1)
		handle_1_philo(data, id);
	else
		rotine(&data->philos[id]);
	fireforce(data);
}

int	simulation(t_data *data)
{
	size_t	i;

	i = 0;
	data->stop->__align = 0;
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
	waitfor_death(data, i);
	return (SUCCESS);
}
