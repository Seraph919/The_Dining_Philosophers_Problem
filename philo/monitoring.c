/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:09:18 by asoudani          #+#    #+#             */
/*   Updated: 2025/04/18 12:12:49 by asoudani         ###   ########.fr       */
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
		pthread_mutex_lock(&data->mut_keep_iter);
		if (data->no_one_died == false)
		{
			pthread_mutex_unlock(&data->mut_keep_iter); // * return unlock for 25 lines..
			break ;
		}
		if (philo_died(&philos[i]) && data->no_one_died)
		{
			data->no_one_died = false;
			pthread_mutex_unlock(&data->mut_keep_iter);
			break ;
		}
		if (i == data->philo_nbrs - 1)
			i = -1;
		pthread_mutex_unlock(&data->mut_keep_iter);
		usleep(1000);
	}
	return (NULL);
}

// void	*all_full_routine(void *data_p)
// {
// 	t_data	*data;
// 	int		i;

// 	data = (t_data *)data_p;
// 	i = -1;
// 	while (++i < data->nb_philos && data->no_one_died)
// 	{
// 		usleep(1000);
// 		if (is_philo_full(data, &data->philos[i]) == false)
// 			i = -1;
// 	}
// 	// if (data->no_one_died)
// 	// {
// 	// 	set_keep_iterating(data, false);
// 	// 	// notify_all_philos(data);
// 	// }
// 	return (NULL);
// }
