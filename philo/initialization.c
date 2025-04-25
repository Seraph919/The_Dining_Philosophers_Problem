/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:44:30 by asoudani          #+#    #+#             */
/*   Updated: 2025/04/25 15:57:31 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	initialization(t_data *data, char **av)
{
	data->meal_nbr = 0;
	data->no_one_died = true;
	data->philo_nbrs = ft_atol(av[1]);
	data->time2die = ft_atol(av[2]);
	data->time2eat = ft_atol(av[3]);
	data->time2sleep = ft_atol(av[4]);
	data->max_nmeals = -1;
	if (av[5])
		data->max_nmeals = ft_atol(av[5]);
	data->philos = malloc(sizeof(t_philo) * data->philo_nbrs);
	if (!data->philos)
		return (ERROR);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_nbrs);
	if (!data->forks)
		return (free(data->philos), ERROR);
	data->philo_ths = malloc(sizeof(pthread_t) * data->philo_nbrs);
	if (!data->philo_ths)
		return (free(data->philos), free(data->forks), ERROR);
	if (mutex_inits(data) == ERROR)
		return (ERROR);
	if (philo_init(data) == ERROR)
		return (ERROR);
	if (forks_init(data) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int	mutex_inits(t_data *data)
{
	if (pthread_mutex_init(&data->eat_mutex, NULL) != 0)
		return (ERROR);
	if (pthread_mutex_init(&data->phile_died_mutex, NULL) != 0)
		return (ERROR);
	if (pthread_mutex_init(&data->print_lock, NULL) != 0)
		return (ERROR);
	if (pthread_mutex_init(&data->meal_counter_mutex, NULL) != 0)
		return (ERROR);
	if (pthread_mutex_init(&data->non_dead_mutex, NULL) != 0)
		return (ERROR);
	return (SUCCESS);
}

int	forks_init(t_data *data)
{
	int		i;
	t_philo	*philos;

	philos = data->philos;
	i = -1;
	while (++i < data->philo_nbrs)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (ERROR);
	}
	philos[0].left_f = &data->forks[0];
	philos[0].right_f = &data->forks[data->philo_nbrs - 1];
	i = 0;
	while (++i < data->philo_nbrs)
	{
		philos[i].left_f = &data->forks[i];
		philos[i].right_f = &data->forks[i - 1];
	}
	return (SUCCESS);
}

int	philo_init(t_data *data)
{
	t_philo	*philos;
	int		i;

	i = -1;
	philos = data->philos;
	while (++i < data->philo_nbrs)
	{
		philos[i].data = data;
		philos[i].id = i + 1;
		philos[i].full = false;
		philos[i].nb_meals_had = 0;
		if (pthread_mutex_init(&philos[i].full_mutex, NULL) != 0)
			return (ERROR);
		if (pthread_mutex_init(&philos[i].last_eat_mutex, NULL) != 0)
			return (ERROR);
		pthread_mutex_lock(&philos[i].last_eat_mutex);
		philos[i].last_eat_time = ms_curr_time();
		pthread_mutex_unlock(&philos[i].last_eat_mutex);
	}
	return (SUCCESS);
}
