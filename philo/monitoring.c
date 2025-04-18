/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:09:18 by asoudani          #+#    #+#             */
/*   Updated: 2025/04/18 13:54:24 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	*all_alive_routine(void *s_data)
{
	int		i;
	t_data	*data;
	t_philo	*philos;

	data = (t_data *)s_data;
	philos = data->philos;
	i = -1;
	while (++i < data->philo_nbrs)
	{
		pthread_mutex_lock(&data->non_dead_mutex);
		if (data->no_one_died == false)
		{
			pthread_mutex_unlock(&data->non_dead_mutex); // * return unlock for 25 lines..
			break ;
		}
		if (philo_died(&philos[i]) && data->no_one_died)
		{
			data->no_one_died = false;
			pthread_mutex_unlock(&data->non_dead_mutex);
			break ;
		}
		if (i == data->philo_nbrs - 1)
			i = -1;
		pthread_mutex_unlock(&data->non_dead_mutex);
		usleep(1000);
	}
	return (NULL);
}
