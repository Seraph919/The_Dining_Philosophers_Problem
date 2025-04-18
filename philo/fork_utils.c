/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:00:29 by asoudani          #+#    #+#             */
/*   Updated: 2025/04/18 18:25:03 by asoudani         ###   ########.fr       */
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
	if (take_left_fork(philo) != 0 || philo_died(philo))
	{
		if (philo_died(philo))
			return (pthread_mutex_unlock(philo->left_f), ERROR);
	}
	if (take_right_fork(philo) != 0 || philo_died(philo))
	{
		if (philo_died(philo))
			pthread_mutex_unlock(philo->right_f);
		pthread_mutex_unlock(philo->left_f);
		return (ERROR);
	}
	return (SUCCESS);
}

int	right_first(t_philo *philo)
{
	if (take_right_fork(philo) != 0 || philo_died(philo))
	{
		if (philo_died(philo))
			return (pthread_mutex_unlock(philo->right_f), ERROR);
	}
	if (take_left_fork(philo) != 0 || philo_died(philo))
	{
		if (philo_died(philo))
			pthread_mutex_unlock(philo->left_f);
		pthread_mutex_unlock(philo->right_f);
		return (ERROR);
	}
	return (SUCCESS);
}

int	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
		return (left_first(philo));
	return (right_first(philo));
}
