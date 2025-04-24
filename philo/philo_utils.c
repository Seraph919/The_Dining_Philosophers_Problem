/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 20:25:10 by asoudani          #+#    #+#             */
/*   Updated: 2025/04/22 12:10:44 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	philo_died(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->phile_died_mutex);
	if (ms_curr_time() - philo->last_eat_time > data->time2die)
	{
		pthread_mutex_unlock(&data->phile_died_mutex);
		return (true);
	}
	pthread_mutex_unlock(&data->phile_died_mutex);
	return (false);
}

void	handle_1_philo(t_philo *philo)
{
	take_left_fork(philo);
	mssleep(philo->data->time2die, philo->data);
	pthread_mutex_unlock(philo->left_f);
	pthread_mutex_lock(&philo->data->non_dead_mutex);
	philo->data->no_one_died = false;
	pthread_mutex_unlock(&philo->data->non_dead_mutex);
	print_msg(philo->data, philo->id, DIED);
}

void	fireforce(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_nbrs)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].last_eat_mutex);
	}
	pthread_mutex_destroy(&data->phile_died_mutex);
	pthread_mutex_destroy(&data->meal_counter_mutex);
	pthread_mutex_destroy(&data->eat_mutex);
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->non_dead_mutex);
	free(data->philo_ths);
	free(data->philos);
	free(data->forks);
}

void	print_msg(t_data *data, int id, char *msg)
{
	size_t	time;
	bool	not_full;

	pthread_mutex_lock(&data->meal_counter_mutex);
	not_full = data->philos[id -1].nb_meals_had != data->max_nmeals;
	pthread_mutex_unlock(&data->meal_counter_mutex);
	time = ms_curr_time() - data->start_time;
	pthread_mutex_lock(&data->print_lock);
	pthread_mutex_lock(&data->non_dead_mutex);
	if (data->no_one_died)
	{
		pthread_mutex_unlock(&data->non_dead_mutex);
		if (id % 2)
			printf(BLUE "%zu %d %s\n" RESET, time, id, msg);
		else
			printf(GREEN "%zu %d %s\n" RESET, time, id, msg);
	}
	else if (msg[0] == 'd' && not_full)
	{
		pthread_mutex_unlock(&data->non_dead_mutex);
		printf(RED "%zu %d %s\n" RESET, time, id, DIED);
	}
	else
		pthread_mutex_unlock(&data->non_dead_mutex);
	pthread_mutex_unlock(&data->print_lock);
}
