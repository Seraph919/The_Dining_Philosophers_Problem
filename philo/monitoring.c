/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:09:18 by asoudani          #+#    #+#             */
/*   Updated: 2025/04/25 14:32:02 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	full(t_data *data, int i)
{
	static int	all_full;

	pthread_mutex_lock(&data->meal_counter_mutex);
	if (data->max_nmeals != -1
		&& data->philos[i].nb_meals_had >= data->max_nmeals)
	{
		all_full++;
		if (all_full == data->philo_nbrs)
			return (pthread_mutex_unlock(&data->meal_counter_mutex), true);
	}
	pthread_mutex_unlock(&data->meal_counter_mutex);
	return (false);
}

void	*monitor(void *arg)
{
	int		i;
	t_data	*data;
	t_philo	*philos;

	data = (t_data *)arg;
	philos = data->philos;
	i = -1;
	while (++i < data->philo_nbrs)
	{
		pthread_mutex_lock(&data->non_dead_mutex);
		if (data->no_one_died == false)
			return (pthread_mutex_unlock(&data->non_dead_mutex), NULL);
		if (full(data, i))
			return (pthread_mutex_unlock(&data->non_dead_mutex), NULL);
		if (philo_died(&philos[i]) && data->no_one_died)
			return (data->no_one_died = false,
				pthread_mutex_unlock(&data->non_dead_mutex),
				print_msg(data, philos[i].id, DIED), NULL);
		if (i == data->philo_nbrs - 1)
			i = -1;
		pthread_mutex_unlock(&data->non_dead_mutex);
		usleep(1000);
	}
	return (NULL);
}
