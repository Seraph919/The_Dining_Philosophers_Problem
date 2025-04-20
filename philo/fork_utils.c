/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:00:29 by asoudani          #+#    #+#             */
/*   Updated: 2025/04/20 14:56:11 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_left_fork(t_philo *philo)
{
	if (philo_died(philo))
		return (1);
	pthread_mutex_lock(philo->left_f);
	print_msg(philo->data, philo->id, TAKE_FORKS);
	return (0);
}

int	take_right_fork(t_philo *philo)
{
	if (philo_died(philo))
		return (1);
	pthread_mutex_lock(philo->right_f);
	print_msg(philo->data, philo->id, TAKE_FORKS);
	return (0);
}

int	left_first(t_philo *philo)
{
	int	res;

	res = take_left_fork(philo);
	if (res != 0 || philo_died(philo))
	{
		if (philo_died(philo) && res == 0)
			return (pthread_mutex_unlock(philo->left_f), ERROR);
		else
			return (ERROR);
	}
	res = take_right_fork(philo);
	if (res != 0 || philo_died(philo))
	{
		if (philo_died(philo) && res == 0)
			pthread_mutex_unlock(philo->right_f);
		pthread_mutex_unlock(philo->left_f);
		return (ERROR);
	}
	return (SUCCESS);
}

int	right_first(t_philo *philo)
{
	int	res;

	res = take_right_fork(philo);
	if (res != 0 || philo_died(philo))
	{
		if (philo_died(philo) && res == 0)
			return (pthread_mutex_unlock(philo->right_f), ERROR);
		else
			return (ERROR);
	}
	res = take_left_fork(philo);
	if (res != 0 || philo_died(philo))
	{
		if (philo_died(philo) && res == 0)
			pthread_mutex_unlock(philo->left_f);
		pthread_mutex_unlock(philo->right_f);
		return (ERROR);
	}
	return (SUCCESS);
}

int	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->non_dead_mutex);
	if (philo->data->no_one_died == false)
	{
		pthread_mutex_unlock(&philo->data->non_dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->non_dead_mutex);
	if (philo->id % 2 == 0)
		return (left_first(philo));
	return (right_first(philo));
}
