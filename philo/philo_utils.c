/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 20:25:10 by asoudani          #+#    #+#             */
/*   Updated: 2025/04/18 18:24:50 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	philo_died(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->die_mutex);
	if (get_time() - philo->last_eat_time > data->time2die)
	{
		pthread_mutex_unlock(&data->die_mutex);
		return (true);
	}
	pthread_mutex_unlock(&data->die_mutex);
	return (false);
}

void	handle_1_philo(t_philo *philo)
{
	take_left_fork(philo);
	usleepp(philo->data->time2die);
	pthread_mutex_unlock(philo->left_f);
	pthread_mutex_lock(&philo->data->non_dead_mutex);
	philo->data->no_one_died = false;
	pthread_mutex_unlock(&philo->data->non_dead_mutex);
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
	pthread_mutex_destroy(&data->die_mutex);
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

	time = get_time() - data->start_time;
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
	else
		pthread_mutex_unlock(&data->non_dead_mutex);
	pthread_mutex_unlock(&data->print_lock);
}
