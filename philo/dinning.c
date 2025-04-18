/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinning.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:01:54 by asoudani          #+#    #+#             */
/*   Updated: 2025/04/18 12:10:16 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *philo_p)
{
	t_philo	*philo;

	philo = (t_philo *) philo_p;
	pthread_mutex_lock(&philo->data->die_mutex);
	philo->last_eat_time = get_time();
	pthread_mutex_unlock(&philo->data->die_mutex);
	if (philo->id % 2 == 0)
		usleepp(philo->data->time2eat - 10);
	if (philo->data->philo_nbrs == 1)
		return (handle_1_philo(philo), NULL);
	while (1)
	{
		if (eating(philo) != 0)
			break;
		pthread_mutex_lock(&philo->data->mut_keep_iter);
		if (philo->data->no_one_died == false)
		{
			pthread_mutex_unlock(&philo->data->mut_keep_iter);
			break;
		}
		pthread_mutex_unlock(&philo->data->mut_keep_iter);
		if (sleeping(philo) != 0)
			break;
		pthread_mutex_lock(&philo->data->mut_keep_iter);
		if (philo->data->no_one_died == false)
		{
			pthread_mutex_unlock(&philo->data->mut_keep_iter);
			break;
		}
		pthread_mutex_unlock(&philo->data->mut_keep_iter);
		if (thinking(philo) != 0)
			break;
		pthread_mutex_lock(&philo->data->mut_keep_iter);
		if (philo->data->no_one_died == false)
		{
			pthread_mutex_unlock(&philo->data->mut_keep_iter);
			break;
		}
		pthread_mutex_unlock(&philo->data->mut_keep_iter);
	}
	return (NULL);
}

void release_forks(t_philo *philo, bool odd)
{
	if (odd)
	{
		pthread_mutex_unlock(philo->left_f);
		pthread_mutex_unlock(philo->right_f);
	}
	else
	{
		pthread_mutex_unlock(philo->right_f);
		pthread_mutex_unlock(philo->left_f);
	}
}

int	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mut_keep_iter);
	if (philo->data->no_one_died == false || (philo->nb_meals_had >=
			philo->data->max_nmeals && philo->data->max_nmeals != -1))
	{
		pthread_mutex_unlock(&philo->data->mut_keep_iter);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->mut_keep_iter);
	if (philo->id % 2)
		usleep(200);
	if (philo->data->philo_nbrs < 100)
		usleep(500);
	if (take_forks(philo) != 0)
		return (return_error("Failed to take forks\n"));
	print_msg(philo->data, philo->id, EAT);
	pthread_mutex_lock(&philo->data->die_mutex);
	philo->last_eat_time = get_time();
	pthread_mutex_unlock(&philo->data->die_mutex);
	usleepp(philo->data->time2eat);
	philo->nb_meals_had++;
	release_forks(philo, philo->id % 2);
	return (0);
}

int	sleeping(t_philo *philo)
{
	print_msg(philo->data, philo->id, SLEEP);
	usleepp(philo->data->time2sleep);
	pthread_mutex_lock(&philo->data->mut_keep_iter);
	if (philo->data->no_one_died == false)
	{
		pthread_mutex_unlock(&philo->data->mut_keep_iter);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->mut_keep_iter);
	return (0);
}

int	thinking(t_philo *philo)
{
	print_msg(philo->data, philo->id, THINK);
	pthread_mutex_lock(&philo->data->mut_keep_iter);
	if (philo->data->no_one_died == false)
	{
		pthread_mutex_unlock(&philo->data->mut_keep_iter);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->mut_keep_iter);
	return (0);
}
