/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asoudani <asoudani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:01:54 by asoudani          #+#    #+#             */
/*   Updated: 2025/04/22 11:55:09 by asoudani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->phile_died_mutex);
	philo->last_eat_time = ms_curr_time();
	pthread_mutex_unlock(&philo->data->phile_died_mutex);
	if (philo->id % 2 == 0)
		mssleep(philo->data->time2eat - 10, philo->data);
	if (philo->data->philo_nbrs == 1)
		return (handle_1_philo(philo), NULL);
	while (1)
	{
		pthread_mutex_lock(&philo->data->non_dead_mutex);
		if (philo->data->no_one_died == false)
			return (pthread_mutex_unlock(&philo->data->non_dead_mutex), NULL);
		pthread_mutex_unlock(&philo->data->non_dead_mutex);
		if (eating(philo) != 0)
			break ;
		if (sleeping(philo) != 0)
			break ;
		if (thinking(philo) != 0)
			break ;
	}
	return (NULL);
}

void	release_forks(t_philo *philo, bool odd)
{
	if (odd)
	{
		pthread_mutex_unlock(philo->left_f);
		pthread_mutex_unlock(philo->right_f);
		return ;
	}
	pthread_mutex_unlock(philo->right_f);
	pthread_mutex_unlock(philo->left_f);
}

int	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->non_dead_mutex);
	if (philo->data->no_one_died == false
		|| (philo->nb_meals_had >= philo->data->max_nmeals
			&& philo->data->max_nmeals != -1))
	{
		philo->data->no_one_died = false;
		pthread_mutex_unlock(&philo->data->non_dead_mutex);
		return (ERROR);
	}
	pthread_mutex_unlock(&philo->data->non_dead_mutex);
	if (philo->id % 2)
		usleep(200);
	if (philo->data->philo_nbrs < 100)
		usleep(500);
	if (take_forks(philo) != 0)
		return (ERROR);
	print_msg(philo->data, philo->id, EAT);
	pthread_mutex_lock(&philo->data->phile_died_mutex);
	philo->last_eat_time = ms_curr_time();
	pthread_mutex_unlock(&philo->data->phile_died_mutex);
	mssleep(philo->data->time2eat, philo->data);
	pthread_mutex_lock(&philo->data->meal_counter_mutex);
	philo->nb_meals_had++;
	pthread_mutex_unlock(&philo->data->meal_counter_mutex);
	return (release_forks(philo, philo->id % 2), SUCCESS);
}

int	sleeping(t_philo *philo)
{
	print_msg(philo->data, philo->id, SLEEP);
	pthread_mutex_lock(&philo->data->non_dead_mutex);
	if (philo->data->no_one_died == false
		|| (philo->nb_meals_had >= philo->data->max_nmeals
			&& philo->data->max_nmeals != -1))
	{
		pthread_mutex_unlock(&philo->data->non_dead_mutex);
		return (ERROR);
	}
	pthread_mutex_unlock(&philo->data->non_dead_mutex);
	mssleep(philo->data->time2sleep, philo->data);
	return (SUCCESS);
}

int	thinking(t_philo *philo)
{
	print_msg(philo->data, philo->id, THINK);
	pthread_mutex_lock(&philo->data->non_dead_mutex);
	if (philo->data->no_one_died == false
		|| (philo->nb_meals_had >= philo->data->max_nmeals
			&& philo->data->max_nmeals != -1))
	{
		pthread_mutex_unlock(&philo->data->non_dead_mutex);
		return (ERROR);
	}
	pthread_mutex_unlock(&philo->data->non_dead_mutex);
	return (SUCCESS);
}
